# Architecture

I followed a MVC pattern for this assignment.

The views is the user interface, and the actions that come along with it, such as viewing a specific city,
or deleting a city.

The controller is what modifies the data.

The models are stored as classes and located inside a datarepository.

Each request from the view to the controller goes through a router. This follows the mediator design pattern, where the frontend does 
not need to understand the inner workings of the backend, such as "Backends for Frontends".

Services are usuable code that is throughout the application, creating greater seperation of business logic that is 
not directly related to the models.

## Write-Ahead Log

This project uses a write-ahead log (WAL) to ensure data durability. All state-changing operations (CREATE_CITY, UPDATE_CITY, DELETE_CITY)
are logged to a binary file before being applied to the data models. On startup, the application replays all logged requests to reconstruct
the previous state. This guarantees no data loss even if the application crashes unexpectedly.

# Running the code:

`make; ./exec.exe`
