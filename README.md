# Vending Machine Simulation

This project simulates a simple vending machine using C. It allows users to interact with the vending machine as customers or as the owner, providing various functionalities such as purchasing items, checking balance, and managing inventory.

## Features

### Customer Features:
- View available items
- Insert money
- Check balance
- Check item prices
- Purchase items
- Retrieve change

### Owner Features:
- Add new items
- Restock existing items
- Check item quantities
- Remove items from the machine
- View total sales

## Compilation

To compile the program, use a C compiler such as GCC:

```
gcc vending_machine.c -o vending_machine
```

## Running the Program

After compilation, run the program using:

```
./vending_machine
```

## Usage

Upon running the program, you'll be presented with a menu of options:

1. Insert money
2. Check balance
3. Check price
4. Purchase
5. Return change
6. Owner menu
7. Exit

### Customer Actions:
- Use option 1 to add money to your balance.
- Use option 2 to check your current balance.
- Use option 3 to check the price of a specific item (you'll need to enter the item's label).
- Use option 4 to purchase an item (you'll need to enter the item's label).
- Use option 5 to retrieve any remaining balance as change.

### Owner Actions:
Access the owner menu using option 6. In the owner menu, you can:
- Add new items to the machine
- Restock existing items
- Check the quantity of items
- Remove items from the machine
- Check total sales

## Notes

- The vending machine is initialized with a 3x3 grid of items.
- Each item has a unique label (e.g., A1, B2, C3).
- The program does not persist data between runs. All changes are lost when the program is closed.
