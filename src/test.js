console.log(__dirname, __filename)
let path = require('path')
let { ginit } = require(path.resolve(`${__dirname}/build/lib/napi_sample.node`));

let js_callback = function (...rest) {
    console.log('【callback】', rest)
    document.getElementById('sdkContainer').innerHTML = rest;
}

// console.log('test export => shutdown', shutdown)

window.onload = function () {
    
    console.log('test export=>', ginit);
    console.log('test call=>', ginit(js_callback));
}