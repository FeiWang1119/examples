package counters

// alertCounter is an unexported type that contains an integer counter for alerts.
type alertCounter int

// New creates and returns valute of the unexported type alertCounter.
func New(value int) alertCounter {
	return alertCounter(value)
}

// type User struct {
// 	Name  string
// 	email string // unexported field email
// }

type user struct {
	Name  string
	Email string
}

type Admin struct {
	user      // The embedded type is unexported.
	Rights int
}
