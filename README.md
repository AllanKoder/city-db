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

# Usage Guide

Once the application is running, you can perform the following operations:

## Supported Operations

**CREATE_CITY** - Add a new city with mayor information
- Provide city name, history, population, year established, and coordinates (latitude, longitude)
- Include mayor name and address
- All changes are automatically logged for durability

**UPDATE_CITY** - Modify an existing city
- Update city history, population, year, or coordinates
- Modify associated mayor information
- Changes are logged and persist across restarts

**DELETE_CITY** - Remove a city from the database
- All associated data is deleted and logged

**GET_ALL_CITIES** - View all cities in the database
- Returns a list of all stored cities with their information

**GET_CITIES** - Query a specific city by name
- Search for city by name
- Returns detailed information including mayor details

**DISPLAY_MAYOR** - View mayor information
- Retrieve details about a city's mayor

**DISTANCE_BETWEEN_CITIES** - Calculate geographic distance
- Compute distance between two cities using their coordinates
- Useful for spatial queries

All data-modifying operations are automatically persisted via the write-ahead log, ensuring your data survives application restarts or crashes.
