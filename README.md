# Boat Monitor

## ToDo

- Update the client to accept a request body
  - i.e. look for the `content-length` header, then decide whether to bail at the first newline or read extra beyond that

## Requirements

- Display current voltage level
  - Read from analog input 1
  - minimum 0V @ 0V, max 15.5V @ 3.3V
- Display bilge level
  - Read from analog input 2
  - minimum 0% @ 0V, maximum 100% @ 3.3V
- Reset cameras
  - protected by a hard-coded password
  - driven by Digital output 1
  - high (3.3V) by default
  - drops low (0V) when triggered and stays there for 30 seconds

## PreReqs
- PlatformIO extension

## To Build
- `make gen`
- click the `update and monitor` option in the PIO extension