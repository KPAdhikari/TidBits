//https://www.w3schools.com/nodejs/nodejs_modules.asp
//You can create your own modules, and easily include them in your applications.
//The following example creates a module that returns a date and time object:
//Use the exports keyword to make properties and methods available outside the module file.


exports.myDateTime = function () {
  return Date();
};
