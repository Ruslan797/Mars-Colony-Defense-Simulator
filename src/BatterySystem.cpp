#include "BatterySystem.h"

BatterySystem::BatterySystem(double maxEnergy)
{
    this->maxEnergy = maxEnergy; // set maximum battery energy

    this->currentEnergy = maxEnergy; // battery starts fully charged
}

void BatterySystem::consume(double amount)
{
    currentEnergy -= amount; // reduce battery energy

    if (currentEnergy < 0)
    {
        currentEnergy = 0; // prevent negative energy
    }
}

void BatterySystem::recharge()
{
    currentEnergy = maxEnergy; // restore full energy
}

double BatterySystem::getCurrentEnergy() const
{
    return currentEnergy; // return current energy
}

double BatterySystem::getMaxEnergy() const
{
    return maxEnergy; // return max energy
}

double BatterySystem::getEnergyPercent() const
{
    return (currentEnergy / maxEnergy) * 100.0; // return energy percent
}

bool BatterySystem::isLow() const
{
    return getEnergyPercent() <= 20.0; // low battery threshold
}

void BatterySystem::recharge(double amount)
{
    currentEnergy += amount; // add charge

    if (currentEnergy > maxEnergy)
    {
        currentEnergy = maxEnergy; // battery cannot exceed maximum
    }
}