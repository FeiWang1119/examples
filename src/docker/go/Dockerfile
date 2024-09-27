FROM golang AS build

WORKDIR /app

COPY go.mod .
COPY go.sum .
RUN go mod download

COPY *.go ./

RUN go build -o /docker-gs-ping-roach

##
## Deploy
##

FROM debian

WORKDIR /

COPY --from=build /docker-gs-ping-roach /docker-gs-ping-roach

EXPOSE 8080

# USER nonroot:nonroot

ENTRYPOINT ["/docker-gs-ping-roach"]
