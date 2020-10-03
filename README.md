# Gossip Membership Protocol

Gossip membership protocol implementation and simulation

## What is gossip membership protocol in distributed systems?

> "In data centers, failures are the norm rather than the exception"

In distributed systems, there is a constant necessity to find what nodes are up and which ones have failed. The goal of a membership protocol is to allow nodes to detect that other nodes have failed.

There are several ways for this to be implemented. One of them is to have a central node that every other node sends heartbeats to. If a node stops sending heartbeats, it is considered failed. However, what if the central node itself fails? Another option would be to have each node send heartbeats to every other node. This is very expensive to the network, as there are N^2 messages for every heartbeat cycle.

The **gossip membership protocol** tackles this problem by sending its heartbeat to only a few other nodes, along with information about other nodes that it has heard from recently. The idea is to have its heartbeat propagate like a gossip, from one peer to another. More information about it can be found [here](https://www.coursera.org/lecture/cloud-computing/2-3-gossip-style-membership-iisnX)

## This implementation

The implementation in this repository is really basic. The node gossips to a random peer and sends its entire membership table in the message. The implementation is robust against both node failures and messages lost during transmission, as shown in the simulation. Node failure chance and message drop ratio can be changed in `Config.hpp`.

Better implementations take notice of the network topology, choosing peers that are closer to itself (like in the same rack) as a way to decrease usage on routers. Also, it is not necessary to send the entire table on every message, as a way to decrease network usage, at a cost of more false positives.
