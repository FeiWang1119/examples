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
	testArray()
	fmt.Println("Hello, World!")
}

func testArray() {
	
	// Declare an array1 of 5 ints
	var array1 [5]int
	fmt.Println(array1)

	// Declare an array2 of 5 ints. The array2 is initialized with the values 1, 2, 3, 4, and 5.
	array2 := [5]int{1, 2, 3, 4, 5}
	array2[2] = 20
	fmt.Println(array2)

	// Only arrays of the same type can be assigned.
	// the type of an array variable includes the length and the type of data that can be stored in each element.
	array1 = array2  // the type of array1 is [5]int
	

	// Declare an array3 of 5 ints. The array3 is initialized with the values 1, 2, 3, 4, and 5.
	// Capacity is determined based on the number of values initialized.
	array3 := [...]int{1, 2, 3, 4, 5}
	fmt.Println(array3)

	// Declare an array4 of 5 ints.
	// Initialize index 1 with the value 10, and index 2 with the value 20.
	// The rest of the elements are initialized with the zero value for the int type.
	array4 := [...]int{1: 10, 2: 20}
	fmt.Println(array4)
	

	array5 := [5]*int{0:new(int), 1:new(int)}
	*array5[0] = 10
	*array5[1] = 20
	fmt.Println(array5)
	
	// Declare a two-dimensional array of four elements by two elements.
	array6 := [4][2]int{{1, 2}, {3, 4}, {5, 6}, {7, 8}}
	fmt.Println(array6)

	// Declare and Initialize individual elements of the outer and inner arrays.
	array7 := [4][2]int{1: {0:20}, 3: {1:30}}
	array7[0][0] = 10
	array7[0][1] = 20
	array7[1][0] = 30
	array7[1][1] = 40

	array6 = array7 // the type of array6 and array7 are [4][2]int

	// copy the second element of array7 to array8
	var array8 [2]int = array7[1]
	fmt.Println(array8)
}
	
