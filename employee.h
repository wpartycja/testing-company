#pragma once

class Employee {
protected:
    const uint id;
    const uint wage;
    uint hoursWorked;

    virtual uint bonus();

public:
    Employee(uint id, uint wage);

    uint getSalary();

    uint getId();
};