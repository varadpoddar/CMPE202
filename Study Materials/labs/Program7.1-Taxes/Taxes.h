#ifndef TAXES_H_
#define TAXES_H_

class GeneralTax
{
public:
    virtual ~GeneralTax() {}

    virtual double amount_owed(const double income) const
    {
        return GENERAL_RATE*income;
    }

private:
    const double GENERAL_RATE = 0.10;
};

class LocalTax : public GeneralTax
{
public:
    double amount_owed(const double earnings) const override
    {
        return LOCAL_RATE*earnings;
    }

private:
    const double LOCAL_RATE = 0.05;
};

class MaxTax : public GeneralTax
{
public:
    double amount_owed(const double amount) const override
    {
        return LOCAL_RATE*amount + GeneralTax::amount_owed(amount);
    }

private:
    const double LOCAL_RATE = 0.05;
};

#endif /* TAXES_H_ */
