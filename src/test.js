let path = require('path')
let _isDev = process.env.NODE_ENV === 'development';
let { ginit, asyncMethod } = _isDev || true ? require(path.resolve(__dirname, '../build/lib/napi_sample.node')) : require('gogtest');

let js_callback = function (...rest) {
    console.log('【callback】', rest)
    if (_isDev) document.getElementById('sdkContainer').innerHTML = `${rest}  ${_isDev}`;
}

// console.log('test export => shutdown', shutdown)
console.log('【test.js】 call=>', ginit(js_callback, 1));
(function () {
    let param = {
        timeSpan: 6,
        callBack: (err, result) => {
            if (err) {
                console.log("callback an error: ", err);
            } else {
                console.log("callback array:" + result);
            }
        },
    };
    let result = asyncMethod(param);
    console.log("asyncMethod", result);
    param.timeSpan = 4;
    result = asyncMethod(param);
    console.log("asyncMethod", result);
})()


// window.onload = function () {
    
//     console.log('test export=>', ginit);
//     console.log('test call=>', ginit(js_callback));
// }