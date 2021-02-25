#include "fmc.h"

bool FmcSdram::sendCommand(const bool bank1,
                           const bool bank2,
                           const Fmc::Mode mode,
                           const uint8_t numberOfAutorefresh,
                           const uint16_t modeRegister)
{
        ::setRegister(rg()->SDCMR,
                             SDCMR::MODE, mode,
                             SDCMR::CTB2, bank2,
                             SDCMR::CTB1, bank1,
                             SDCMR::NRFS, numberOfAutorefresh - 1,
                             SDCMR::MRD, modeRegister);

        static uint32_t timeout = 0xffffff;

        do {

        }while (::getRegField(rg()->SDSR, SDSR::BUSY) &&
                (timeout--));

        if (timeout)
                return true;
        else
                return false;
}
