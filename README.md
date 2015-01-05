Page-stats-simulator
====================

Given page trace file simulator generates number of page accesses, number of page hits, number of page misses for each page. It also gives total number of accesses, hits and misses and generates page misses for each core.

Trace file follows format like below:
Core Id Page Number

One major task left is to trun program in asynchronous reads so that lru and file read can occur simultaneously.
