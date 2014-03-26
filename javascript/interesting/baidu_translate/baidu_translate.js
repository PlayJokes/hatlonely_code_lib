// @desc  百度语言翻译机 
//          http://www.programfan.com/acm/show.asp?qid=112
//          1. 映射关系读到一个map中
//          2. map中的key按照字符长度排序，可以实现最大匹配
//          3. 用正则表达式匹配一次替换
// @file  baidu_translate.js
// @auth  hatlonely (hatlonely@gmail.com)
// @date  2014-3-26


var fs = require('fs');

function makeMapAndKeys(mapPath, encoding) {
    encoding = encoding ? encoding : 'utf-8';
    var mapData = fs.readFileSync(mapPath, encoding);
    var lines = mapData.split('\n');
    var translateMap = {};
    var translateKeys = [];

    for (var i = 0; i < lines.length; i++) {
        var kv = lines[i].trim().split(' ');
        translateMap[kv[0]] = kv[1];
        translateKeys.push(kv[0]);
    }

    translateKeys.sort(function (str1, str2) {
        if (str1.length == str2.length) {
            return str1 > str2;
        }
        return str1.length < str2.length;
    });

    return {
        translateMap: translateMap,
        translateKeys: translateKeys
    }
}

function translate(mapAndKeys, docPath, encoding) {
    encoding = encoding ? encoding : 'utf-8';
    var translateMap = mapAndKeys.translateMap;
    var translateKeys = mapAndKeys.translateKeys;
    var text = fs.readFileSync(docPath, encoding);

    for (var i = 0; i < translateKeys.length; i++) {
        text = text.replace(new RegExp(translateKeys[i], 'gm'),
            translateMap[translateKeys[i]]);
    }
    return text;
}

console.log(translate(makeMapAndKeys('baidu_translate_test_doc_map'),
    'baidu_translate_test_doc_to_translate'));