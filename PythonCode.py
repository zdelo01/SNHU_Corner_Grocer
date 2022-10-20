filename = 'items.txt'

'''
Zachary DeLong
CS-210
10/16/2022
'''

'''
Gets the list of lines read in from the file in raw form.
@param - the filename to read in (must be in same directory as the Source.cpp!)
@return - the list of lines
'''
def readFile(filename):

    lines = []
    
    with open(filename) as file:
        lines = file.readlines()
    
    return lines

'''
Get the inventory read in from the file.
@return - dictionary of inventory in the form {item : frequency}
'''
def getInventory():
   
    # Dictionary of {item : frequency} 
    inventory = {}
    
    items = readFile(filename)

    # Loop through the list of items
    for item in items:
     
        item = item.strip()

        # Update existing frequency; otherwise add item to dictionary
        if item in inventory:
            # Accumulate to the dictionary item
            inventory[item] = inventory.get(item, 0) + 1 
        else:
            # Add new item to dictionary
            inventory[item] = 1
            
    return inventory

'''
Description: Get inventory & loops through sorted inventory and prints items with their frequencies
param - N/A
return - N/A
'''
def determineInventory():
    # Get the inventory
    inventory = getInventory()

    for key in sorted(inventory):
        print("{}: {}".format(key, inventory[key]))

'''
Description: Get inventory and return frequency of the item given by the param
Example: item = 'Apples' -> inventory is called and counts occurrence of 'Apples' -> returns 4
param item - string param passed from callIntFunc("determineFrequency", item)
return - item frequency
'''
def determineFrequency(item):
    # Get the inventory
    inventory = getInventory()
    if item in inventory:
        frequency = inventory[item]
        return frequency
    else:
        return 0
    

''' 
Description: Get the inventory & loop through sorted inventory and write word frequencies to "frequency.dat"
param - N/A
return - N/A
'''
def output():
    # Get the inventory
    inventory = getInventory()
    frequency = open("frequency.dat", "w")
    lastKey = len(sorted(inventory)) 
    iteration = 0

    for key in sorted(inventory):     
        iteration += 1
        # Will not leave a new line after last entry in the sorted dictionary
        if (iteration == lastKey ): 
            frequency.write("{} {}".format(key, inventory[key]))
        else:
            frequency.write("{} {}\n".format(key, inventory[key]))
    # Close file
    frequency.close()