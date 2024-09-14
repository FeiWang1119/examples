package main

import (
	"fmt"
	"html/template"
	"net/http"
	"strconv"
)

// Change the signature of the home handler so it is defined as a method against
// *application.
func (app *application) home(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path != "/" {
		app.noFound(w) // Use the noFound() helper.
		return
	}

	// Initialize a slice containing the paths to the two files. Note that the home.page.template
	// file must be the "first" file in the slice.
	// Include the footer partial in the template files.
	files := []string{
		"./ui/html/home.page.tmpl", 
		"./ui/html/base.layout.tmpl", 
		"./ui/html/footer.partial.tmpl",
	}

	// Use the template.ParseFiles()) function to read the template file into a template set.
	// If there is an error, we log the detailed error message and the http.Error() function
	// to send a generic 500 Internal Server Error response to the user.
	// Notice that we can pass the slice of file paths as a variadic parameter.
	ts, err := template.ParseFiles(files...)
	if err != nil {
		app.serveError(w, err) // Use the serveError() helper.
		return
	}

	// We then use the Execute() method on the template set to write the template content
	// as the response body. The last parameter to Execute() represents dynamic data that
	// we want to pass in, which for now we'll leave as nil.
	err = ts.Execute(w, nil)
	if err != nil {
		app.serveError(w, err) // Use the serveError() helper.
	}
}

// Change the signature of the showSnippet handler so it is defined as a method against
// *application.
func (app *application) showSnippet(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(r.URL.Query().Get("id"))
	if err != nil || id < 1 {
		app.notFound(w) // Use the notFound() helper.
		return
	}
	fmt.Fprintf(w, "Display a specific snippet with ID %d...", id)
}

// Change the signature of the createSnippet handler so it is defined as a method against
// *application.
func (app *application) createSnippet(w http.ResponseWriter, r *http.Request) {
	if r.Method != "POST" {
		w.Header().Set("Allow", "POST")
		app.clientError(w, http.StatusMethodNotAllowed) // Use the clientError() helper.
		return
	}

	w.Write([]byte("Create a new snippet..."))
}
