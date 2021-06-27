package main

import "fmt"

func main() {
     fmt.Printf("hello, world\n")
}


/*
############### kp: Installation #############
kp: 4/3/18:    https://golang.org/doc/install
############### kp: Installation #############

Mac OS X package installer

Download the package file, open it, and follow the prompts to install the Go tools. The package installs the Go distribution to /usr/local/go.

The package should put the /usr/local/go/bin directory in your PATH environment variable. You may need to restart any open Terminal sessions for the change to take effect.

############### Test your Installation #############

 Check that Go is installed correctly by setting up a workspace and building a simple program, as follows.

Create your workspace directory, $HOME/go. (If you'd like to use a different directory, you will need to set the GOPATH environment variable.)

Next, make the directory src/hello inside your workspace, and in that directory create a file named hello.go like this.

 Then build it with the go tool:

$ cd $HOME/go/src/hello
$ go build

The command above will build an executable named hello in the directory alongside your source code. Execute it to see the greeting:

$ ./hello
hello, world

##############
(kp: we can also do 'go run hello.go' to compile and run at the same time. This way, it seems, the executable is deleted after execution or it simply runs as a python code would do in it's shell or interpreter. The 'go build' command created an executable of name 'hello' that had the size of 2 MB - a pretty big file for a very small source file which had the size of 1.6 K.)
#############

If you see the "hello, world" message then your Go installation is working.

You can run go install to install the binary into your workspace's bin directory or go clean to remove it.

Before rushing off to write Go code please read the How to Write Go Code document, which describes some essential concepts about using the Go tools.
Uninstalling Go

To remove an existing Go installation from your system delete the go directory. This is usually /usr/local/go under Linux, Mac OS X, and FreeBSD or c:\Go under Windows.

You should also remove the Go bin directory from your PATH environment variable. Under Linux and FreeBSD you should edit /etc/profile or $HOME/.profile. If you installed Go with the Mac OS X package then you should remove the /etc/paths.d/go file. Windows users should read the section about setting environment variables under Windows. 
*/