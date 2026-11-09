/*
Design a Message Bus:
1. A message bus is a class, serving simultaneously multiple clients across multiple threads.
2. Each client has unique identifier 
3. Bus and Clients can exchange messages. Each message contains unique id, identifier of a sending client (sender) and an identifier of a receiving client (receiver). 
    Sender identifier is always unique, receiver, identifier can be or unique or wildcard (broadcast message). 
    Messages should remain persistent until deleted by a client or until retention time is expired, in this case the message should be deleted by Bus
4. Bus provides the following functions to a client:
    1. Send a Message. 
    2. Read a message, this function allows to retrieve a message by specified message id. Read also consumes the message from queue.
    3. Read all messages addressed to a given client.
*/


/*
class Bus:

send message 
read message by id (remove from queue)
readall
*/


/*
class Client:
runs on their thread
has a unique identifier

*/

/*
struct message:
unique message id
unique sender id
unique receiver id (or wildcard, broadcast)
TTL - once depleted, delete by bus
- can be deleted by client
*/