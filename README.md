# OrderBook Matching Engine (C++)

A compact, performant C++ order-book engine supporting price-time priority matching, efficient order insertion, cancellation, and clear order book visualization. Designed specifically to demonstrate fundamental market microstructure concepts, ideal for MSc Computational Finance applications.

## Features

- **Price-Time Priority Matching**: Matches orders by best price and earliest submission time.
- **Efficient Data Structures**: `std::map` and `std::deque` for fast insertion and lookup.
- **O(1) Order Cancellation**: Uses `std::unordered_map` for rapid order cancelation.
- **Clear Visualization**: Built-in function to display the current state of the order book.

## Build Instructions

### GCC / Clang

```bash
g++ -std=c++17 -O3 OrderBook.cpp -o orderbook
./orderbook
```

### Visual Studio (2019+)

1. Create a new C++ Console Application.
2. Set Language Standard to C++17 (`/std:c++17`).
3. Add `OrderBook.cpp` to your project and build (Ctrl+Shift+B).

## Example Usage

Sample output demonstrating basic functionality:

```
TRADE 3 @ 99.5
TRADE 4 @ 105

-- OrderBook Snapshot --
BIDS:
  100 | qty=7 | id=1
ASKS:
  (empty)
```


## Licensing

Distributed under the MIT License. See `LICENSE` file for more details.

---

For academic purposes: developed as a demonstration of market microstructure concepts and C++ engineering practices.
