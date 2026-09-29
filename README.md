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

After running the application, you'll see a `db >` prompt. Enter commands to interact with the city database.

## Available Commands

**add <city_name>**
- Creates a new city. You'll be prompted to enter city history, population, year of establishment, coordinates, and mayor information.
- Example: `add London`

**update <city_name>**
- Modifies an existing city's information including history, population, year, coordinates, and mayor details.
- Example: `update London`

**delete <city_name>**
- Removes a city and all its associated data from the database.
- Example: `delete London`

**display city <city_name>**
- Shows all details for a specific city.
- Example: `display city London`

**display cities**
- Shows all cities in the database.
- Example: `display cities`

**display mayor <city_name>**
- Shows the mayor information for a specific city.
- Example: `display mayor London`

**distance <city_name_1> <city_name_2>**
- Calculates the geographic distance between two cities based on their coordinates.
- Example: `distance London Paris`

**history <city_name>**
- Displays the history of a specific city.
- Example: `history London`

**population <city_name>**
- Displays the population of a specific city.
- Example: `population London`

**year <city_name>**
- Displays the year a city was established.
- Example: `year London`

**coordinates <city_name>**
- Displays the latitude and longitude coordinates of a city.
- Example: `coordinates London`

**sorted cities**
- Displays all cities in sorted order.
- Example: `sorted cities`

**seed <number>**
- Generates sample city data for testing. Useful for populating the database quickly.
- Example: `seed 5`

**save**
- Manually saves all pending changes to the write-ahead log.
- Example: `save`

**help**
- Shows all available commands.
- Example: `help`

**exit**
- Exits the application and saves all data.
- Example: `exit`
