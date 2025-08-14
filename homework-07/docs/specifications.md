# Online Cinema System - Technical Specifications

## 1. System Overview
This document provides a detailed technical specification for the Online Cinema system. It serves as a complement to the UML diagrams and outlines the core components, their responsibilities, and how they interact to provide the system's functionality. The system supports user registration, movie browsing, content management, and the purchasing and renting of movies.

## 2. Use Case Specification

### Actors
- **RegisteredUser**: An authenticated user who can perform all core actions such as purchasing, renting, and managing their profile.
- **Guest**: An unauthenticated user who can only browse the movie catalog and perform registration or login.
- **Admin**: A user with elevated privileges to manage system content and user accounts.

### Use Cases
- **Browse Movies**: Allows `Guest` and `RegisteredUser` to view the movie catalog.
- **Login / Register**: Allows `Guest` users to authenticate or create a new account.
- **Purchase Movie**: A `RegisteredUser` can buy a movie. This process includes payment and granting permanent access to the film.
- **Rent Movie**: A `RegisteredUser` can rent a movie for a limited period. This process includes payment and granting temporary access.
- **Watch Movie**: Allows a `RegisteredUser` to view a movie they have purchased or rented.
- **Manage Content**: An `Admin` can add, remove, or modify movie data.
- **Manage Users**: An `Admin` can manage user accounts and their privileges.

## 3. Class Specification

## Key Classes
- `User` **(Base Class)**: A foundational class with basic user attributes (`userId`, `username`, `email`, `password`) and methods (`login()`, `logout()`).
- `RegisteredUser`: Inherits from `User`. Includes additional attributes like `firstName`, `lastName`, and lists for `purchaseHistory` and `rentalHistory`. Methods include `rentMovie()`, `purchaseMovie()`, and `addReview()`.
- `Administrator`: Inherits from `User`. Contains specific administrative methods like `manageContent()` and `manageUsers()`.
- `Movie`: Represents a film with attributes like `movieId`, `title`, `description`, `releaseYear`, and prices for purchase/rental.
- `Rental`: Represents a temporary license for a movie with attributes like `rentalId`, `rentalDate`, and `expirationDate`. It is linked to a `RegisteredUser` and a `Movie`.
- `PaymentMethod`: Stores user payment details (e.g., `cardType`, `cardNumber`) and methods for processing transactions.
- `Review`: Represents a user's review of a movie, including a `rating` and `comment`.

### Relationships
- **Inheritance**: `RegisteredUser` and `Administrator` are subclasses of `User`.
- **Association**: `RegisteredUser` has a one-to-many relationship with `Purchase`, `Rental`, `PaymentMethod`, and `Review`. `Movie` also has a one-to-many relationship with `Review`.
- **Aggregation**: `Movie` has a one-to-many relationship with `Genre`, meaning a movie can have multiple genres, but a genre can exist independently of a specific movie.

## 4. Sequence Diagram Specification

### Scenario: User buys a movie
This scenario outlines the process from movie selection to successful purchase. The `User Interface` communicates with the `Server`, which then handles payment processing via the `PaymentGateway` and updates the `Database` before confirming the purchase to the user.

### Scenario: User watches a rented movie
This scenario details the dynamic flow for accessing a rented movie.
1. The `UserInterface` requests to start watching from the `RentalService`.
2. The `RentalService` performs a `self-validation` check and then contacts the `PaymentGateway` to verify the `payment status` and `rental validity`.
3. Based on the check result, the system either:
    - **Success Path**: Requests a movie stream from the `StreamingService` and returns the stream link to the user.
    - **Failure Path**: Sends an error message to the user interface, informing the user that the rental is no longer valid.

## 5. State Diagram Specification

**States of the `Rental` Object**
- `Created`: The initial state. An object enters this state when a user initiates a rental but before payment is processed.
- `Active`: The rental is active and the movie is available for viewing. This state is entered from `Created` upon successful payment.
- `Expired`: The rental period has ended. The object enters this state automatically from `Active` when the rental period expires.
- `Canceled`: The rental was cancelled by the user. This is a terminal state that can be reached from both `Created` and `Active`.

**Transitions**
- `Created` -> `Active`: Triggered by `Payment Processed`.
- `Created` -> `Canceled`: Triggered by `Cancel`.
- `Active` -> `Expired`: Triggered by Rental `Period Expires`.
- `Active` -> `Canceled`: Triggered by `Cancel`.
- `Active` -> `Active`: Triggered by `Extend (Successful Renewal Payment)`, which refreshes the rental period.