/*
 * Copyright (C) 2007, 2008 Apple Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @constructor
 * @extends {WebInspector.Object}
 * @implements {WebInspector.ContentProvider}
 * @param {?WebInspector.NetworkRequest} request
 * @param {string} url
 * @param {string} documentURL
 * @param {NetworkAgent.FrameId} frameId
 * @param {NetworkAgent.LoaderId} loaderId
 * @param {WebInspector.ResourceType} type
 * @param {string} mimeType
 * @param {boolean=} isHidden
 */
WebInspector.Resource = function(request, url, documentURL, frameId, loaderId, type, mimeType, isHidden)
{
    this._request = request;
    this.url = url;
    this._documentURL = documentURL;
    this._frameId = frameId;
    this._loaderId = loaderId;
    this._type = type || WebInspector.resourceTypes.Other;
    this._mimeType = mimeType;
    this.history = [];
    this._isHidden = isHidden;

    /** @type {?string} */ this._content;
    /** @type {boolean} */ this._contentEncoded;
    this._pendingContentCallbacks = [];
    if (this._request && !this._request.finished)
        this._request.addEventListener(WebInspector.NetworkRequest.Events.FinishedLoading, this._requestFinished, this);
    
    this._restoreRevisionHistory();
}

WebInspector.Resource.Events = {
    RevisionAdded: "revision-added",
    MessageAdded: "message-added",
    MessagesCleared: "messages-cleared",
}

WebInspector.Resource.prototype = {
    /**
     * @return {?WebInspector.NetworkRequest}
     */
    get request()
    {
        return this._request;
    },

    /**
     * @return {string}
     */
    get url()
    {
        return this._url;
    },

    set url(x)
    {
        this._url = x;
        this._parsedURL = new WebInspector.ParsedURL(x);
    },

    get parsedURL()
    {
        return this._parsedURL;
    },

    /**
     * @return {string}
     */
    get documentURL()
    {
        return this._documentURL;
    },

    /**
     * @return {NetworkAgent.FrameId}
     */
    get frameId()
    {
        return this._frameId;
    },

    /**
     * @return {NetworkAgent.LoaderId}
     */
    get loaderId()
    {
        return this._loaderId;
    },

    /**
     * @return {string}
     */
    get displayName()
    {
        return this._parsedURL.displayName;
    },

    /**
     * @return {WebInspector.ResourceType}
     */
    get type()
    {
        return this._request ? this._request.type : this._type;
    },

    /**
     * @return {string}
     */
    get mimeType()
    {
        return this._request ? this._request.mimeType : this._mimeType;
    },

    /**
     * @return {Array.<WebInspector.ConsoleMessage>}
     */
    get messages()
    {
        return this._messages || [];
    },

    /**
     * @param {WebInspector.ConsoleMessage} msg
     */
    addMessage: function(msg)
    {
        if (!msg.isErrorOrWarning() || !msg.message)
            return;

        if (!this._messages)
            this._messages = [];
        this._messages.push(msg);
        this.dispatchEventToListeners(WebInspector.Resource.Events.MessageAdded, msg);
    },

    /**
     * @return {number}
     */
    get errors()
    {
        return this._errors || 0;
    },

    set errors(x)
    {
        this._errors = x;
    },

    /**
     * @return {number}
     */
    get warnings()
    {
        return this._warnings || 0;
    },

    set warnings(x)
    {
        this._warnings = x;
    },

    clearErrorsAndWarnings: function()
    {
        this._messages = [];
        this._warnings = 0;
        this._errors = 0;
        this.dispatchEventToListeners(WebInspector.Resource.Events.MessagesCleared);
    },

    /**
     * @return {?string}
     */
    get content()
    {
        return this._content;
    },

    /**
     * @return {boolean}
     */
    get contentEncoded()
    {
        return this._contentEncoded;
    },

    /**
     * @param {string} newContent
     * @param {function(String)=} callback
     */
    _setContent: function(newContent, callback)
    {
        var uiSourceCode = this._uiSourceCode;
        if (!this._uiSourceCode || !this._uiSourceCode.isEditable())
            return;
        this._uiSourceCode.setWorkingCopy(newContent);
        this._uiSourceCode.commitWorkingCopy(callback);
    },

    /**
     * @param {string} content
     * @param {Date=} timestamp
     * @param {boolean=} restoringHistory
     */
    addRevision: function(content, timestamp, restoringHistory)
    {
        if (this.history.length) {
            var lastRevision = this.history[this.history.length - 1];
            if (lastRevision._content === content)
                return;
        }
        var revision = new WebInspector.Revision(this, content, timestamp || new Date());
        this.history.push(revision);

        this.dispatchEventToListeners(WebInspector.Resource.Events.RevisionAdded, revision);
        if (!restoringHistory)
            revision._persist();
        WebInspector.resourceTreeModel.dispatchEventToListeners(WebInspector.ResourceTreeModel.EventTypes.ResourceContentCommitted, { resource: this, content: content });
    },

    _restoreRevisionHistory: function()
    {
        if (!window.localStorage)
            return;

        WebInspector.Revision._ensureStaleRevisionsFileteredOut();
        var registry = WebInspector.Revision._revisionHistoryRegistry();
        var historyItems = registry[this.url];
        for (var i = 0; historyItems && i < historyItems.length; ++i)
            this.addRevision(window.localStorage[historyItems[i].key], new Date(historyItems[i].timestamp), true);
    },

    _clearRevisionHistory: function()
    {
        if (!window.localStorage)
            return;

        var registry = WebInspector.Revision._revisionHistoryRegistry();
        var historyItems = registry[this.url];
        for (var i = 0; historyItems && i < historyItems.length; ++i)
            delete window.localStorage[historyItems[i].key];
        delete registry[this.url];
        window.localStorage["revision-history"] = JSON.stringify(registry);
    },
   
    /**
     * @return {?string}
     */
    contentURL: function()
    {
        return this._url;
    },

    /**
     * @return {WebInspector.ResourceType}
     */
    contentType: function()
    {
        return this.type;
    },

    /**
     * @param {function(?string, boolean, string)} callback
     */
    requestContent: function(callback)
    {
        if (typeof this._content !== "undefined") {
            callback(this._content, !!this._contentEncoded, this.canonicalMimeType());
            return;
        }

        this._pendingContentCallbacks.push(callback);
        if (!this._request || this._request.finished)
            this._innerRequestContent();
    },

    canonicalMimeType: function()
    {
        return this.type.canonicalMimeType() || this.mimeType;
    },

    /**
     * @param {string} query
     * @param {boolean} caseSensitive
     * @param {boolean} isRegex
     * @param {function(Array.<WebInspector.ContentProvider.SearchMatch>)} callback
     */
    searchInContent: function(query, caseSensitive, isRegex, callback)
    {
        /**
         * @param {?Protocol.Error} error
         * @param {Array.<PageAgent.SearchMatch>} searchMatches
         */
        function callbackWrapper(error, searchMatches)
        {
            callback(searchMatches || []);
        }

        if (this.frameId)
            PageAgent.searchInResource(this.frameId, this.url, query, caseSensitive, isRegex, callbackWrapper);
        else
            callback([]);
    },

    /**
     * @param {Element} image
     */
    populateImageSource: function(image)
    {
        function onResourceContent()
        {
            image.src = this._contentURL();
        }

        this.requestContent(onResourceContent.bind(this));
    },

    /**
     * @return {string}
     */
    _contentURL: function()
    {
        const maxDataUrlSize = 1024 * 1024;
        // If resource content is not available or won't fit a data URL, fall back to using original URL.
        if (this._content == null || this._content.length > maxDataUrlSize)
            return this.url;

        return "data:" + this.mimeType + (this._contentEncoded ? ";base64," : ",") + this._content;
    },


    _requestFinished: function()
    {
        this._request.removeEventListener(WebInspector.NetworkRequest.Events.FinishedLoading, this._requestFinished, this);
        if (this._pendingContentCallbacks.length)
            this._innerRequestContent();
    },


    _innerRequestContent: function()
    {
        if (this._contentRequested)
            return;
        this._contentRequested = true;

        /**
         * @param {?Protocol.Error} error
         * @param {string} content
         * @param {boolean} contentEncoded
         */
        function callback(error, content, contentEncoded)
        {
            this._content = error ? null : content;
            this._contentEncoded = contentEncoded;
            var callbacks = this._pendingContentCallbacks.slice();
            for (var i = 0; i < callbacks.length; ++i)
                callbacks[i](this._content, this._contentEncoded, this.canonicalMimeType());
            this._pendingContentCallbacks.length = 0;
            delete this._contentRequested;
        }
        PageAgent.getResourceContent(this.frameId, this.url, callback.bind(this));
    },

    revertToOriginal: function()
    {
        function revert(content)
        {
            this._setContent(content, function() {});
        }
        this.requestContent(revert.bind(this));
    },

    revertAndClearHistory: function(callback)
    {
        function revert(content)
        {
            this._setContent(content, clearHistory.bind(this));
        }

        function clearHistory()
        {
            this._clearRevisionHistory();
            this.history = [];
            callback();
        }

        this.requestContent(revert.bind(this));
    },

    /**
     * @return {boolean}
     */
    isHidden: function()
    {
        return !!this._isHidden; 
    },

    /**
     * @return {WebInspector.UISourceCode}
     */
    uiSourceCode: function()
    {
        return this._uiSourceCode;
    },

    /**
     * @param {WebInspector.UISourceCode} uiSourceCode
     */
    setUISourceCode: function(uiSourceCode)
    {
        this._uiSourceCode = uiSourceCode;
    }
}

WebInspector.Resource.prototype.__proto__ = WebInspector.Object.prototype;

/**
 * @constructor
 * @implements {WebInspector.ContentProvider}
 * @param {WebInspector.Resource} resource
 * @param {?string|undefined} content
 * @param {Date} timestamp
 */
WebInspector.Revision = function(resource, content, timestamp)
{
    this._resource = resource;
    this._content = content;
    this._timestamp = timestamp;
}

WebInspector.Revision._revisionHistoryRegistry = function()
{
    if (!WebInspector.Revision._revisionHistoryRegistryObject) {
        if (window.localStorage) {
            var revisionHistory = window.localStorage["revision-history"];
            try {
                WebInspector.Revision._revisionHistoryRegistryObject = revisionHistory ? JSON.parse(revisionHistory) : {};
            } catch (e) {
                WebInspector.Revision._revisionHistoryRegistryObject = {};
            }
        } else
            WebInspector.Revision._revisionHistoryRegistryObject = {};
    }
    return WebInspector.Revision._revisionHistoryRegistryObject;
}

WebInspector.Revision._ensureStaleRevisionsFileteredOut = function()
{
    if (!window.localStorage)
        return;

    if (WebInspector.Revision._staleRevisionsFilteredOut)
        return;
    WebInspector.Revision._staleRevisionsFilteredOut = true;
    
    var registry = WebInspector.Revision._revisionHistoryRegistry();
    var filteredRegistry = {};
    for (var url in registry) {
        var historyItems = registry[url];
        var filteredHistoryItems = [];
        for (var i = 0; historyItems && i < historyItems.length; ++i) {
            var historyItem = historyItems[i];
            if (historyItem.loaderId === WebInspector.resourceTreeModel.mainFrame.loaderId) {
                filteredHistoryItems.push(historyItem);
                filteredRegistry[url] = filteredHistoryItems;
            } else
                delete window.localStorage[historyItem.key];
        }
    }
    WebInspector.Revision._revisionHistoryRegistryObject = filteredRegistry;

    function persist()
    {
        window.localStorage["revision-history"] = JSON.stringify(filteredRegistry);
    }

    // Schedule async storage.
    setTimeout(persist, 0);
}

WebInspector.Revision.prototype = {
    /**
     * @return {WebInspector.Resource}
     */
    get resource()
    {
        return this._resource;
    },

    /**
     * @return {Date}
     */
    get timestamp()
    {
        return this._timestamp;
    },

    /**
     * @return {?string}
     */
    get content()
    {
        return this._content || null;
    },

    revertToThis: function()
    {
        function revert(content)
        {
            if (this._resource._content !== content)
                this._resource._setContent(content, function() {});
        }
        this.requestContent(revert.bind(this));
    },

    /**
     * @return {?string}
     */
    contentURL: function()
    {
        return this._resource.url;
    },

    /**
     * @return {WebInspector.ResourceType}
     */
    contentType: function()
    {
        return this._resource.contentType();
    },

    /**
     * @param {function(?string, boolean, string)} callback
     */
    requestContent: function(callback)
    {
        callback(this._content || "", false, this.resource.mimeType);
    },

    /**
     * @param {string} query
     * @param {boolean} caseSensitive
     * @param {boolean} isRegex
     * @param {function(Array.<WebInspector.ContentProvider.SearchMatch>)} callback
     */
    searchInContent: function(query, caseSensitive, isRegex, callback)
    {
        callback([]);
    },

    _persist: function()
    {
        if (!window.localStorage)
            return;

        var url = this.contentURL();
        if (url.startsWith("inspector://"))
            return;

        var loaderId = WebInspector.resourceTreeModel.mainFrame.loaderId;
        var timestamp = this.timestamp.getTime();
        var key = "revision-history|" + url + "|" + loaderId + "|" + timestamp;

        var registry = WebInspector.Revision._revisionHistoryRegistry();

        var historyItems = registry[url];
        if (!historyItems) {
            historyItems = [];
            registry[url] = historyItems;
        }
        historyItems.push({url: url, loaderId: loaderId, timestamp: timestamp, key: key});

        function persist()
        {
            window.localStorage[key] = this._content;
            window.localStorage["revision-history"] = JSON.stringify(registry);
        }

        // Schedule async storage.
        setTimeout(persist.bind(this), 0);
    }
}