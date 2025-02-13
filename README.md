# Data Structures Project: Publish/Subscribe System

## Description

This project simulates a **Publish/Subscribe System** where publishers provide information, and subscribers consume it. The system is designed to manage information groups, subscriptions, and the flow of information between publishers and subscribers. The project focuses on implementing various data structures, including linked lists and arrays, to handle the system's operations efficiently.

### Key Features:
- **Information Groups**: Information is categorized into groups, and each group maintains a list of published information.
- **Subscriptions**: Subscribers can subscribe to specific groups to receive relevant information.
- **Persistent State**: The system stores information to allow new subscribers to access past data.
- **Event Handling**: The system processes events such as inserting new information, registering subscribers, consuming information, and deleting subscribers.

## Data Structures

The project uses the following data structures:
- **Group**: Represents a group of information, containing a list of published information and a list of subscribers.
- **Info**: Represents a piece of information, including its ID, timestamp, and associated groups.
- **Subscription**: Represents a subscription to a group by a subscriber.
- **SubInfo**: Represents a subscriber, including their ID, timestamp, and subscriptions to various groups.

## Contributors

- [Noriana Tzatzai](https://github.com/noriana09)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
