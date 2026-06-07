#pragma once

class BatterySystem
{
private:
    double currentEnergy; // current battery energy
    double maxEnergy;     // maximum battery energy

public:
    BatterySystem(double maxEnergy); // create battery with maximum energy

    void consume(double amount); // use some battery energy

    void recharge(); // recharge battery to full

    double getCurrentEnergy() const; // return current energy

    double getMaxEnergy() const; // return maximum energy

    double getEnergyPercent() const; // return battery percentage

    bool isLow() const; // check if battery is low

    void recharge(double amount); // recharge battery
};