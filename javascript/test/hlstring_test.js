require('hlstring');

console.log('&amp;&gt;&lt;&quot;&amp;&gt;&lt;&quot;'.decodeHTML());
console.log('&amp;&gt;&lt;&quot;&amp;&gt;&lt;&quot;'.decodeHTML2());


for (var i = 0; i < 1000000; i++) {
    '&amp;&gt;&lt;&quot;&amp;&gt;&lt;&quot;&amp;&gt;&lt;&quot;&amp;&gt;&lt;&quot;'.decodeHTML2();
}