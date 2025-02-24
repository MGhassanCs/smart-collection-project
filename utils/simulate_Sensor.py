import random
import time

def simulate_sensor_data():
    # Simulate the sensor reading (percent from 0 to 100)
    percentage = random.randint(0, 100)
    return percentage

def main():
    while True:
        # Get simulated sensor data
        sensor_data = simulate_sensor_data()
        
        # Print the simulated data (to see it in your terminal)
        print(f"Sensor Data (Garbage Can Fullness): {sensor_data}%")
        
        # Wait for 1 second before simulating again
        time.sleep(1)

if __name__ == "__main__":
    main()
