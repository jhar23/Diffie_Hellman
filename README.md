# Diffie Hellman

This repo was created to learn about socket programming and the Diffie Hellman.
So far you will find 3 different file names. Server, Client, and Diffie.

# How to use

As of right now, simply use the `Makefile` to create the executable.

If you want to host, use `./Diffie host` in your terminal.
If you want to be a client to connect to someone else, use `./Diffie client` in your terminal.

## How does Diffie Hellman work?

Diffie Hellman is a key exchange method used to generate a symmetric key that should
send be sent over an authenticated channel. (**Diffie Hellman does not have
any authentication, so it is possible to have a man in the middle attack, unless
the channel is authenticated. A man in the middle attack is not possible if the middle-man
only receives data between the two parties.**)

Suppose two people want to create a key, Alice and Bob. Alice and Bob establish two
public prime numbers, the base number, *g* and the modulus *p*. Alice creates her own random
secret number *a*, and Bob creates his, *b*. Alice and Bob do the same operations using their
secret number to generate the secret key, *s*.

1. *A* = *g*<sup>a</sup> % *p*, *B* = *g*<sup>b</sup> % *p*
2. Alice sends Bob *A* and Bob sends Alice *B*.
3. *s* = *A*<sup>b</sup> % *p* (**Bob**) = *B*<sup>a</sup> % *p* (**Alice**)

The operation is symmetric to both people, so they end up with the same key.
In other words,

(*g*<sup>a</sup> % *p*)<sup>b</sup> % *p* = (*g*<sup>b</sup> % *p*)<sup>a</sup> % *p*

Bob is the operation on the left, and Alice is the operation on the right.
They now have a shared secret key.

The key is secret because it was never sent over the channel to the other person.
Alice did not know Bob's secret number, and vice versa. This means they would not
be able to create the key without the other person, and a man in the middle could not
replicate the key.

## Diffie

Diffie is a class created to manage the different stages in the key exchange.
It first generates a vector of prime numbers, and picks two random numbers from
that vector, one is the base, the other is the modulus.

This class also has functions to create the values needed to send the parts of the key
to the other person.

## Server

Server is where the host creates a socket and listens for connections. Upon finding a connection,
the Server code will start creating a key for the two parties to use.

## Client

Client is where the client will create a socket by connecting to the host, and then communicate
to establish a key.

## Future Plans

In the future I plan to clean up the code for the 3 files currently in the repo, then use the
key that's generated to encrypt a message and have the other person decrypt it using the key.
I will most likely just start with a very simple XOR encryption.
