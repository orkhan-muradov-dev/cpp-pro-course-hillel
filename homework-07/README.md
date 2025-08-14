# Homework \#7: Online Cinema - UML Project

## Task Description

This assignment requires designing the software architecture for an online cinema system using a set of standard **UML diagrams**. The project's goal is to model the system's structure, behavior, and key interactions to provide a clear blueprint for development.

### Requirements

  - Create a **Use Case Diagram** to outline system functionality from the user's perspective.
  - Develop a **Class Diagram** that models the static structure and relationships between core entities.
  - Design **Sequence Diagrams** to illustrate the dynamic flow of key user scenarios.
  - Create a **State Diagram** to model the lifecycle of a critical system object.

-----

## System Description

This project outlines the software design for an online cinema system. The platform allows users to browse a catalog of movies, purchase or rent films, and watch them online. The system supports two primary user types: a **Viewer**, who can interact with the catalog and manage their profile, and an **Administrator**, who is responsible for managing content and users.

-----

## Files

  - `README.md` — The documentation for the project.
  - `diagrams/` — Directory containing all the UML diagram files.
  - `diagrams/use-case.png` — The Use Case diagram.
  - `diagrams/class-diagram.png` — The Class diagram.
  - `diagrams/sequence-purchase.png` — The Sequence diagram for purchasing a movie.
  - `diagrams/sequence-watch-rented-movie.png` — The Sequence diagram for watching a rented movie.
  - `diagrams/state-rental.png` — The State diagram for the `Rental` object.

-----

## Diagrams

### Use Case Diagram

  * **File**: [`use-case.png`](https://www.google.com/search?q=diagrams/use-case.png)
  * **Description**: This diagram illustrates the high-level functionality of the system from the user's perspective. It defines the system's actors (`Guest`, `RegisteredUser`, `Admin`) and their interactions with the system's core use cases. The relationships, such as `<<include>>` and `<<extend>>`, are used to show dependencies and optional behaviors, providing a clear overview of the system's scope.

### Class Diagram

  * **File**: [`class-diagram.png`](https://www.google.com/search?q=diagrams/class-diagram.png)
  * **Description**: A detailed diagram that models the static structure of the system. It defines the main classes (`User`, `Movie`, `Purchase`, `Rental`, `Review`, `PaymentMethod`, etc.), their attributes, and their methods. This diagram also specifies the relationships between classes, such as inheritance (e.g., `RegisteredUser` inheriting from `User`), association, and aggregation, which are crucial for understanding the data model.

### Sequence Diagrams

  * **File**: [`sequence-purchase.png`](https://www.google.com/search?q=diagrams/sequence-purchase.png)

  * **Description**: This diagram visualizes the flow of actions and interactions between system components for the "User buys a movie" scenario. It shows the temporal sequence of messages passed between objects, from movie selection and authorization to payment processing and final access to the movie.

  * **File**: [`sequence-watch-rented-movie.png`](https://www.google.com/search?q=diagrams/sequence-watch-rented-movie.png)

  * **Description**: This diagram details the dynamic flow for the "User watches a rented movie" scenario. It highlights the sequence of events and the conditional logic (`alt` block) for handling a valid rental versus an expired one, providing insight into the system's real-time behavior.

### State Diagram

  * **File**: [`state-rental.png`](https://www.google.com/search?q=diagrams/state-rental.png)
  * **Description**: This diagram models the lifecycle of the `Rental` object. It outlines the different states an object can be in (`Created`, `Active`, `Expired`, `Canceled`) and the events that trigger transitions between these states, such as `Payment Processed` or `Rental Period Expires`. This is essential for understanding the object's behavior over time.

-----

## Technical Decisions

The system's design, particularly as shown in the sequence diagrams, reflects a modern, service-oriented architecture. Core functionalities like rental validation and payment processing are handled by distinct, specialized services (`RentalService`, `PaymentGateway`, `StreamingService`). This approach promotes a clear **separation of concerns**, which enhances the system's scalability (new services can be added easily), maintainability (services can be updated independently), and resilience (the failure of one service does not necessarily crash the entire system).

-----

## Instruments

All diagrams were created using **[Draw.io](draw.io) [(diagrams.net)](diagrams.net)**.