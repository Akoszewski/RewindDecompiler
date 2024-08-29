#ifndef ANALYSER_HPP
#define ANALYSER_HPP

#include "Function.hpp"

#include <optional>
#include <map>

enum class RegStatus
{
    Unknown,
    IsKnownNumber,
    IsEqualToOtherUnit
};

struct Register
{
    RegStatus status = RegStatus::Unknown;
    long long value = 0;
    bool wasChanged = false;
    unsigned char byteSize;
    std::string qwordVersionName;
    std::string dwordVersionName;
    std::string wordVersionName;
    std::string byteVersionName;
    std::string highByteVersionName;
    Register() = default;
    Register(int size, const std::string& qwVersionName, const std::string& dwVersionName, const std::string& wVersionName,
                const std::string& bVersionName, const std::string& hbVersionName)
      : byteSize(size)
      , qwordVersionName(qwVersionName)
      , dwordVersionName(dwVersionName)
      , wordVersionName(wVersionName)
      , byteVersionName(bVersionName)
      , highByteVersionName(hbVersionName)
    {}
};

class Analyser
{
public:
    Analyser();
    bool isFromFunctionPrologue(const Instruction& instruction);
    bool isFromFunctionEpilogueExceptRet(const Instruction& instruction);
    std::optional<Function> findFunctionWithAddress(int address);
    void initFunctionParameters(Function& function);
    std::string getParentRegisterName(const std::string& regName);
    bool isParameterRegister(const std::string& regName);
    std::map<std::string, Register> registerMap;
    std::vector<std::string> parameterRegisters;
    std::map<unsigned char, std::string> sizeToTypeMap;
};

#endif
