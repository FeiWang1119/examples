// the executable program must have a package main, or compiler will regard it as an package, like hello, not an executable / command
// the package is intented to be compiled into an binary executable

package main

// compiler would look for the package "fmt" in the following places:
// 1. The Go installation directory where standard library source code is contained, e,g, /usr/local/go/src/pkg/fmt
// 2. Each directory listed in the GOPATH environment variable.

import "fmt"

// import "strings" output an error whenever the compiler finds a package that you don't use.
// sometimes need to import a package that you don't need to reference identifiers from.
// e.g. just to call init function from a package, you can use the blank identifier _ to rename an import.

// remote imports
// import "github.com/golang/example/stringutil"
// the Go tooling will download the package from the remote repository and place it in the GOPATH at the location that matches the URL
// the fetching is done using the go get command. go get will fetch any specified packages and their dependencies.
// since go get is recursive, it can walk down the source code tree for a package and fetch all the dependencies it finds.

// import multiple packages with the same name. e.g. import "network/convert" and import "file/convert"
// both packages will be imported by using named imports
// the is performed by giving one of the packages a new name to the left of the import statement.
// import (
// 	"network/convert"
// 	fileconvert "file/convert"
// )

// each package can have many init functions, which are called prior to main funcion being executed
func init() {
	fmt.Println("init function")
}

// compiler must find a function named main in main package, which is the entry point for the program
func main() {
	fmt.Println("Hello, World!")
}
