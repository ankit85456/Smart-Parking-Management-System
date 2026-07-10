#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <limits>
#include <ctime> // For getting the current time

//==============================================================================
// OOP: Using a struct to represent a Vehicle
// This groups all related data for a single vehicle into one object,
// which is a fundamental concept of Object-Oriented Programming.
//==============================================================================
struct Vehicle {
    std::string ownerName;
    std::string vehicleNo;
    int slotNo;
    std::string vehicleType;
    std::string inTime;
};

//==============================================================================
// Utility Function to get current time as a string
//==============================================================================
std::string getCurrentTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return buf;
}

//==============================================================================
// Main Function
// The entry point of the application.
//==============================================================================
int main() {
    // --- DSA: Core Data Structures ---
    // 1. A vector to store the list of all currently parked vehicles.
    std::vector<Vehicle> parkedVehicles;
    // 2. A stack to keep track of the last action for the "Undo" feature.
    std::stack<Vehicle> historyStack;

    int choice;

    // Main application loop
    do {
        // --- Display Menu ---
        std::cout << "\n--- Smart Parking Management System ---\n";
        std::cout << "1. Park a Vehicle\n";
        std::cout << "2. Unpark a Vehicle\n";
        std::cout << "3. Search for a Vehicle\n";
        std::cout << "4. Check Parking Status\n";
        std::cout << "5. Undo Last Parking Action\n";
        std::cout << "6. Exit\n";
        std::cout << "---------------------------------------\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice;

        // --- Input Validation ---
        if (std::cin.fail()) {
            std::cout << "\n[Error] Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // --- Process User Choice ---
        switch (choice) {
            case 1: { // Park a Vehicle
                Vehicle newVehicle;
                std::cout << "Enter Owner Name: ";
                std::getline(std::cin, newVehicle.ownerName);
                std::cout << "Enter Vehicle Number: ";
                std::getline(std::cin, newVehicle.vehicleNo);
                std::cout << "Enter Slot Number: ";
                std::cin >> newVehicle.slotNo;
                std::cout << "Enter Vehicle Type (e.g., 2-Wheeler): ";
                std::cin.ignore(); // Clear buffer before getline
                std::getline(std::cin, newVehicle.vehicleType);

                newVehicle.inTime = getCurrentTime();

                parkedVehicles.push_back(newVehicle);
                historyStack.push(newVehicle); // Save action for undo

                std::cout << "\n[Success] Vehicle parked at " << newVehicle.inTime << std::endl;
                break;
            }
            case 2: { // Unpark a Vehicle
                int slot;
                std::cout << "Enter Slot Number to unpark: ";
                std::cin >> slot;
                bool found = false;
                for (auto it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it) {
                    if (it->slotNo == slot) {
                        std::cout << "\n[Success] Vehicle " << it->vehicleNo << " unparked.\n";
                        parkedVehicles.erase(it);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "\n[Error] No vehicle found in slot " << slot << std::endl;
                }
                break;
            }
            case 3: { // Search for a Vehicle
                std::string vehicleNum;
                std::cout << "Enter Vehicle Number to search: ";
                std::getline(std::cin, vehicleNum);
                bool found = false;
                for (const auto& vehicle : parkedVehicles) {
                    if (vehicle.vehicleNo == vehicleNum) {
                        std::cout << "\n--- Vehicle Found ---\n";
                        std::cout << "Owner: " << vehicle.ownerName << std::endl;
                        std::cout << "Vehicle No: " << vehicle.vehicleNo << std::endl;
                        std::cout << "Slot No: " << vehicle.slotNo << std::endl;
                        std::cout << "Type: " << vehicle.vehicleType << std::endl;
                        std::cout << "In-Time: " << vehicle.inTime << std::endl;
                        std::cout << "---------------------\n";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "\n[Error] Vehicle with number " << vehicleNum << " not found.\n";
                }
                break;
            }
            case 4: { // Check Parking Status
                std::cout << "\n--- Parking Status ---\n";
                std::cout << "Total Parked Vehicles: " << parkedVehicles.size() << std::endl;
                std::cout << "----------------------\n";
                break;
            }
            case 5: { // Undo Last Parking Action
                if (historyStack.empty()) {
                    std::cout << "\n[Info] No parking action to undo.\n";
                } else {
                    Vehicle lastParked = historyStack.top();
                    historyStack.pop();

                    // Find and remove the last parked vehicle from the main list
                    for (auto it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it) {
                        if (it->vehicleNo == lastParked.vehicleNo && it->slotNo == lastParked.slotNo) {
                            parkedVehicles.erase(it);
                            break;
                        }
                    }
                    std::cout << "\n[Success] Last parking action for vehicle " << lastParked.vehicleNo << " has been undone.\n";
                }
                break;
            }
            case 6: { // Exit
                std::cout << "\nExiting the program. Goodbye!\n";
                break;
            }
            default: {
                std::cout << "\n[Error] Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 6);

    return 0;
}
