// @file  hlstring.js
// @desc  useful function for javascript string
// @auth  hatlonely(hatlonely@gmail.com)
// @date  2014-3-22

// string lstrip()       strip left space
// string rstrip()       strip right space
// string strip()        strip left and right space
// string ljust(number width, char fillChar)        padding left
// string rjust(number width, char fillChar)        padding right
// string center(number width, char fillChar)       padding left and right
// boolean startWith(string prefix)    test prefix
// boolean endWith(string suffix)      test suffix
// string encodeHTML()   encode with html
// string decodeHTML()   decode from html


// @brief  strip left space
// @return {string} the strip string
String.prototype.lstrip = function () {
    return this.replace(/^\s+/, '');
}

// @brief  strip right space
// @return {string} the strip string
String.prototype.rstrip = function () {
    return this.replace(/\s+$/, '');
}

// @brief  strip left and right space
// @return {string} the strip string
String.prototype.strip = function () {
    return this.replace(/(^\s+)|(\s+$)/g, '');
}

// @brief  padding left
// @param  {number} width width after padding
// @param  {string} fillChar padding with fillChar
// @return {string} the padding string
String.prototype.ljust = function (width, fillChar) {
    fillChar = fillChar || ' ';
    var length = this.length;
    var padding = '';
    for (var i = length; i < width; i++) {
        padding += fillChar;
    }
    return this + padding;
}

// @brief  padding right
// @param  {number} width width after padding
// @param  {string} fillChar padding with fillChar
// @return {string} the padding string
String.prototype.rjust = function (width, fillChar) {
    fillChar = fillChar || ' ';
    var length = this.length;
    var padding = '';
    for (var i = length; i < width; i++) {
        padding += fillChar;
    }
    return padding + this;
}

// @brief  padding left and right
// @param  {number} width width after padding
// @param  {string} fillChar padding with fillChar
// @return {string} the padding string
String.prototype.center = function (width, fillChar) {
    fillChar = fillChar || ' ';
    var length = this.length;
    var padLen = width - length;
    var lPadLen = Math.floor(padLen / 2);
    var rPadLen = padLen - lPadLen;
    var lPadding = '', rPadding = '';
    console.log(lPadLen);
    console.log(rPadLen);
    for (var i = 0; i < lPadLen; i++) {
        lPadding += fillChar;
    }
    for (var i = 0; i < rPadLen; i++) {
        rPadding += fillChar;
    }
    return lPadding + this + rPadding;
}

// @brief  test prefix
// @param  {string} prefix
// @return {boolean} 
String.prototype.startsWith = function (prefix) {
    return this.substr(0, prefix.length) == prefix;
}

// @brief  test suffix
// @param  {stirng} suffix
// @return {boolean}
String.prototype.endsWith = function (suffix) {
    return this.substr(this.length - suffix.length, suffix.length) == suffix;
}

// @brief  encode html
// @return {string} encoded string 
String.prototype.encodeHTML = function () {                                      
    return this.replace(/&/g,'&amp;').replace(/>/g,'&gt;')
            .replace(/</g,'&lt;').replace(/"/g,'&quot;');
}

// @brief  decode html
// @return {string} decoded string
String.prototype.decodeHTML = function () {                                      
    return this.replace(/&amp;/g,'&').replace(/&gt;/g,'>')
            .replace(/&lt;/g,'<').replace(/&quot;/g,'"');
}