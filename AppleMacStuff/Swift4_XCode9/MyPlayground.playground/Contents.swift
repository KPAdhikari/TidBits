//: Playground - noun: a place where people can play

import UIKit

var str = "Hello, playground"
print(str)

var legend = ["aa":"aaa","bb":"bbb"]
for item in legend {
    //print(item)
    print(item.key)
    print(item.value)
}


var  age = 20

switch age {
    
case 14:
    print("Your age is 14")
case 20:
    print("Your age is 20")
    print("What's up?")
case 30:
    print("Your age is 30")
default:
    print("Don't know your age.")
}

//creating a function
func firstFunction () {
    print("Hi! I am your first function.")
}


//Calling the function
firstFunction()
firstFunction()

//Function with input args
func add(num1: Int, num2: Int) {
    print(num1 + num2)
}

add(num1: 2, num2: 3)

//Function with input args and a return statement.
func multiply(num1: Int, num2: Int) -> Int {
    return num1 * num2
}

print(multiply(num1: 5, num2: 3))



enum Direction {
    case North
    case South
    case East
    case West
}

class Person {
    var name : String
    var age : Int
    
    //One of the properties (function) of the class
    init(name: String, age: Int) {
        self.name = name
        self.age = age
    }
    
    func greeting() {
        print("Your name is \(self.name) and you are \(self.age) years old")
    }
}

var person1 = Person(name: "Avi", age: 16)
person1.age
person1.name
person1.greeting()

class Parent {
    func parentMethod() {
        print("Hey, this is from the Parent method")
    }
    func getName() {
        print("Hey, this is Parent.")
    }
}

var p = Parent()
p.parentMethod()

class Child : Parent {
    func childMethod() {
        print("Hey, this is from the Child mehtod")
    }
    
    override func getName() {
        print("This is Child.")
    }
}

var c = Child()
c.childMethod()
c.parentMethod()
c.getName()


