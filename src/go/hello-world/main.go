// the executable program must have a package main, or compiler will regard it as an package, like hello, not an executable / command
// the package is intented to be compiled into an binary executable

package main

// compiler would look for the package "fmt" in the following places:
// 1. The Go installation directory where standard library source code is contained, e,g, /usr/local/go/src/pkg/fmt
// 2. Each directory listed in the GOPATH environment variable.

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

import (
	"fmt"
	"counters"
	// "github.com/linuxdeepin/go-lib/notify"
)

// each package can have many init functions, which are called prior to main funcion being executed
func init() {
	fmt.Println("init function")
}

// compiler must find a function named main in main package, which is the entry point for the program
func main() {
	fmt.Println("Hello, World!")
}

// notifier is an interface that defined notification type behavior.
type notifier interface {
	notify()
}

type user struct {
	name       string
	email      string
	ext        int
	privileged bool
}

// Declaring fields based on other struct types.
type admin struct {
	user // Embedded type as an inner type of the outer type admin
	level  string
}

// notify implements a method with a pointer receiver.
func (u *user) notify() {
	fmt.Printf("name: %s, email: %s, ext: %d, privileged: %t", u.name, u.email, u.ext, u.privileged)
}

// notify implements a method that can be called vi a value of type admin.
// inner type (user)'s implementation was not promoted once the outer type (admin) implemented the notify method.
func (a *admin) notify() {
	fmt.Printf("admin name: %s, email: %s, ext: %d, privileged: %t, level: %s", a.user.name, a.user.email, a.user.ext, a.user.privileged, a.level)
}

// There are two types of receivers in Go: value receivers and pointer receivers.

// Declaration of a method with a value receiver.
// The method will always be operating against a copy of the value used to make the method call.
func (u user) notify0() {
	fmt.Printf("name: %s, email: %s, ext: %d, privileged: %t", u.name, u.email, u.ext, u.privileged)
}

// Declaration of a method with a pointer receiver.
// pointer receivers operate on the actual value.
func (u *user) changeEmail(email string) {
	u.email = email
}

// Decalring of a new type based on an int64
// duration and int64 are two distinct and different types
// var dur duration
// dur = int64(10)
// Compiler error assigning value of different types
type duration int64

// built-in types: numeric, string, and Boolean types
// reference types: slice, map, channel, interface, and function types. All the different
// header values from the different reference types contain a pointer to an underlying
// data structure.
func testType() {
	// Declare a variable of type user, set it to a zero value
	// the zero value of a struct is the zero value for each field of the struct
	var bill user
	println(bill)

	// Declare a variable of the struct type using a struct literal.
	// The short variable declaration operator serves two purposes: it both declares and initializes a variable.
	// The order of the fields dones't matter.
	lisa := user{name: "Lisa", email: "lisa@example.com", ext: 10, privileged: true}
	println(lisa)

	// Create a struct type value without declaring the field names.
	// The order of the fields does matter and need to match the order of the fields in the struct declaration.
	tom := user{"Tom", "tom@example.com", 20, false}
	println(tom)

	fred := admin{
		user: user{
			name:       "Fred",
			email:      "fred@example.com",
			ext:        30,
			privileged: true,
		},
		level: "super",
	}
	
	// access the inner type's method notify directly
	fred.user.notify()

	// the inner type's method is promoted.
	fred.notify()

	//The embedded inner type's implementation of the interface is promoted to the outer type.
	sendNotification(&fred)

	println(fred)

	// calling a method with a value receiver
	// the value of lisa is the receiver of the method call
	// and the notify0 method is operating against a copy of this value.
	lisa.notify0()
	// Value of type user can be used to call methods declared with a pointer receiver.
	// Imagine that Go is performing the following operation:
	// (&lisa).changeEmail("lisa@google.com")
	lisa.changeEmail("lisa@google.com")

	adam := &user{"Adam", "adam@example.com", 40, false}
	// calling a method with a pointer receiver
	// the pointer of lisa is the receiver of the method call
	// the value used to make the call is shared with the method.
	adam.changeEmail("adam@google.com")
	// Pointer of type user can also be used to call methods declared with a value receiver.
	// Imagine that Go is performing the following operation:
	// (*adam).notify0()
	adam.notify0()

	// u := user{"Adam", "adam@example.com", 40, false}
	// sendNotification(u)
	// compiler error: user does not implement notifier (notify method has pointer receiver)
	
	// Looking at these rules from the perspective of the value
	// Methods sets as described by the specification
	// Values         Methods Receivers
    // -----------------------------------------------
    // T             (t T)
    // *T            (t T) and (t *T)
	// 1. a value of type T only has methods declared that have a value receiver.
	// 2. pointers of type T have methods declared with both value and pointer receivers.

	// Looking at these rules from the perspective of receivers
	// Methods Receivers    Values         
    // -----------------------------------------------
    // (t T)                T and *T
    // (t *T)               *T
	// 1. implement an interface using a value receiver, then both the values and pointers of the type implement the interface.
	// 2. implement an interface using a pointer receiver, then only the pointers of the type implement the interface.
	
	// only the pointers of the type implement the interface.
	// The question now is why the restriction?
	// The answer comes from the fact that it's not always possible to get the address of a value.
	u := user{"Adam", "adam@example.com", 40, false}
	sendNotification(&u)

	// Create a varable of the unexported type using the exported New function from the package counters.
	// 1. identifier are exported or unexported, not values.
	// 2. the short variable declaration operator is capable of inferring the type and creating a variable of the unexported type.
	counter := counters.New(10)
	fmt.Println(counter)

	a := counters.Admin{
		Rights: 10,
	}

	// Set the exported field from the unexported inner type.
	// the identifiers from the inner type are promoted to the outer type.
	// those exported fields are known through a value of the outer type.
	// There's no access to the inner type directly.
	a.Name = "admin"
	a.Email = "admin@example.com"
	fmt.Println(a)
}

// sendNotification accepts values that implement the notifier interface.
// and sends notifications.
func sendNotification(n notifier) {
	n.notify()
}

func testMap() {
	// Create a map with a key of type string and a value of type int.
	dict1 := make(map[string]int)
	fmt.Println(dict1)

	// Create a map with a key of type string and a value of type int.
	dict2 := map[string]int{"one": 1, "two": 2, "three": 3}
	fmt.Println(dict2)

	// The map key can be value from any built-in type, or a struct type as long as the value can be used in an expression with the == operator.
	// Slices, functions, and struct types that contain slices cannot be used as map keys.
	// dic := map[[]string]int{} Compiler Exception: invalid map key type []string

	// Assigning values to a map.
	dict3 := map[string]string{}
	dict3["one"] = "1"
	fmt.Println(dict3)

	// Runtime error assigned to a nil map
	// var colors map[string]string
	// colors["red"] = "#FF0000"
	// Runtime Error:
	// panic: runtime error: assignment to entry in nil map

	// Retrieving a value from a map and testing existence.
	color := map[string]string{"red": "#FF0000", "green": "#00FF00", "blue": "#0000FF"}
	value, exists := color["red"]
	if exists {
		fmt.Println(value)
	}

	// Retrieving a value from a map testing the value for existence.
	// when the key doesn't exist, the zero value of the value's type is returned.
	value1 := color["red"]
	if value1 != "" {
		fmt.Println(value1)
	}

	//  iterate over a map using for range
	for key, value := range color {
		fmt.Println(key, value)
	}

	// Removing an item from a map.
	delete(color, "red")
	for key, value := range color {
		fmt.Println(key, value)
	}

	// Passing maps between functions
	// Doesn't make a copy of the map.
	removeColor(color, "blue")
	for key, value := range color {
		fmt.Println(key, value)
	}
}

func removeColor(colors map[string]string, color string) {
	delete(colors, color)
}

func testSlice() {
	// Create a slice of strings by the built-in function make.
	// Contains a length and capacity of 5 elements.
	slice1 := make([]string, 5)
	fmt.Println(slice1)

	// Create a slice of strings.
	// Contains a length of 5 elements and a capacity of 10 elements.
	// compiler error setting capacity less than length
	slice2 := make([]string, 5, 10)
	fmt.Println(slice2)

	// Declaring a slice with a slice literal.
	slice3 := []string{"red", "green", "blue", "yellow", "orange"}
	fmt.Println(slice3)

	// Declaring a slice with index positions.
	// Initialize the 100th element with an empty string.
	slice4 := []string{99: ""}
	fmt.Println(slice4)

	// Declaration difference between array and slice.
	// an array is created, when a value inside the [] operator is specified.
	array := [3]int{1, 2, 3}
	slice5 := []int{1, 2, 3}
	fmt.Println(array)
	fmt.Println(slice5)

	// Declaring a nil slice.
	var slice6 []int
	fmt.Println(slice6)

	// Use make to create an empty slice of integers.
	slice7 := make([]int, 0)
	fmt.Println(slice7)

	// Use a slice literal to create an empty slice of integers.
	slice8 := []int{}
	fmt.Println(slice8)

	slice9 := []int{10, 20, 30, 40, 50}
	// Change the value of index 1, use the [] operator.
	slice9[1] = 25

	// Taking the slice of a slice
	// two slices are sharing the same underlying array(capacity k = 5).
	// Howerver, each slice views the underlying array in a different way.
	// For slice[i:j], or slice[1:3]
	// Length:   j - i or 3 - 1 = 2
	// Capacity: k - i or 5 - 1 = 4
	slice10 := []int{10, 20, 30, 40, 50}
	newSlice := slice10[1:3]
	fmt.Println(newSlice)

	// Changes made to the new slice are reflected in the original slice.
	// Change index 1 of newSlice.
	// Change index 2 of the original slice.
	newSlice[1] = 25
	fmt.Println(slice10)

	// Using append to add an element to a slice.
	// slice10 also see the changes in index 3.
	newSlice = append(newSlice, 60)

	// Using append to increase the length and capacity of a slice.
	// When the capacity of a slice is not sufficient,
	// create a new underlying array, copy the existing values, and assign the new value
	// new slice has own underlying array, and the capacity is doubled from its original size under 1000 elements.
	slice11 := []int{10, 20, 30, 40, 50}
	newSlice1 := append(slice11, 60)
	fmt.Println(newSlice1)

	// performing a three-index slice.
	// For slice[i:j:k], or slice[2:3:4]
	// Length:   j - i or 3 - 2 = 1
	// Capacity: k - i or 4 - 2 = 2
	// Runtime error setting capcity larger than existing capacity
	source := []string{"Apple", "Banana", "Orange", "Mango", "Grape"}
	slice12 := source[2:3:4]
	fmt.Println(slice12)

	// Benifit of setting length and capacity to be the same
	// call append and it will create a new underlying array of two elements
	// copy the fruit orange, add the new fruit pear, return a new slice that references this new underlying array.
	source1 := []string{"Apple", "Banana", "Orange", "Mango", "Grape"}
	slice13 := source1[2:3:3]
	slice13 = append(slice13, "Pear")

	// use the ... operator to append all the elements of one slice into another
	s1 := []int{1, 2}
	s2 := []int{3, 4}
	fmt.Println(append(s1, s2...))

	// iterating over a slice using for range
	// index is the index position of the element in the slice
	// value is a copy of the element in that index position
	slice14 := []int{1, 2, 3, 4, 5}
	for index, value := range slice14 {
		fmt.Println(index, value)
	}

	// Composing slices of slices
	multidimensionalSlice := [][]int{
		{10},
		{100, 200},
	}
	// Appending the value 20 to the first slice of integers.
	multidimensionalSlice[0] = append(multidimensionalSlice[0], 20)
	fmt.Println(multidimensionalSlice)

	// Passubg slices between functions
	// Only the slice is being copied, not the underlying array.
	slice15 := []int{1, 2, 3, 4, 5}
	appendSlice(slice15)
	fmt.Println(slice15)
}

func appendSlice(slice []int) []int {
	slice = append(slice, 6)
	return slice
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
	array1 = array2 // the type of array1 is [5]int

	// Declare an array3 of 5 ints. The array3 is initialized with the values 1, 2, 3, 4, and 5.
	// If the length is given as ..., capacity is determined based on the number of values initialized.
	array3 := [...]int{1, 2, 3, 4, 5}
	fmt.Println(array3)

	// Declare an array4 of 5 ints.
	// Initialize index 1 with the value 10, and index 2 with the value 20.
	// The rest of the elements are initialized with the zero value for the int type.
	array4 := [...]int{1: 10, 2: 20}
	fmt.Println(array4)

	array5 := [5]*int{0: new(int), 1: new(int)}
	*array5[0] = 10
	*array5[1] = 20
	fmt.Println(array5)

	// Declare a two-dimensional array of four elements by two elements.
	array6 := [4][2]int{{1, 2}, {3, 4}, {5, 6}, {7, 8}}
	fmt.Println(array6)

	// Declare and Initialize individual elements of the outer and inner arrays.
	array7 := [4][2]int{1: {0: 20}, 3: {1: 30}}
	array7[0][0] = 10
	array7[0][1] = 20
	array7[1][0] = 30
	array7[1][1] = 40

	array6 = array7 // the type of array6 and array7 are [4][2]int

	// copy the second element of array7 to array8
	var array8 [2]int = array7[1]
	fmt.Println(array8)
}
