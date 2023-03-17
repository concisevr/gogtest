let path = require('path')
let _isDev = process.env.NODE_ENV === 'development'
let { ginit, asyncMethod } = _isDev || true ? require(path.resolve(__dirname, '../build/lib/napi_sample.node')) : require('gogtest');

const client_id = ""

const client_secret = ""

let js_callback = function (...rest) {
    console.log('【callback】', rest)
    if (false) document.getElementById('sdkContainer').innerHTML = `${rest}  ${_isDev}`;
}

console.log('【test.js】 call=>', ginit(js_callback, client_id, client_secret));
console.log('【test.js】 asyncMethod=>', asyncMethod);
(async function () {
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
    setInterval(() => {
        result = asyncMethod(param);
    }, 3000)
})()
