// PlayerUnit class

#pragma once

#include "UnitBase.hpp"

class PlayerUnit : public UnitBase
{
private:
	void SetUnitParameter(Point index) override;
};
