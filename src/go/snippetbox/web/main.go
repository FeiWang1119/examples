package main

import (
	"log"
	"net/http"
)

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", home)
	mux.HandleFunc("/snippets", showSnippet)
	mux.HandleFunc("/snippets/create", createSnippet)

	log.Println("Starting server on :8000")
	err := http.ListenAndServe(":8000", mux)
	log.Fatal(err)
}
