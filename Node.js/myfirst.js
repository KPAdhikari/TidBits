//kp: Ref: https://www.w3schools.com/nodejs/nodejs_get_started.asp
//    Node.js files must be initiated in the "Command Line Interface" program of your computer.
//    To do that, in the terminal do 'node myfirst.js' which makes your computer work as a server
//    If anyone tries to access your computer on port 8080, they will get a "Hello World!" message in return!
//    Start your internet browser, and type in the address: http://localhost:8080
//

//Consider modules to be the same as JavaScript libraries.
//Node.js has a set of built-in modules which you can use without any further installation.
//To include a module, use the require() function with the name of the module:
var http = require('http'); //This is built-in module
var dt = require('./myfirstmodule'); //This is a custom/local module defined by myself.


http.createServer(function (req, res) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write("The date and time are currently: " + dt.myDateTime() + "\n");
    //res.end('Hello World!');
    res.end('<p>Hello World!</p>'); //Without p-tags, 'Hello World!' showed up in the same line.   
    //res.end();
    //}).listen(8080);
}).listen(8080);
