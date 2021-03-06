#include "loaddial.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"
#include "defs.hpp"

namespace ESM
{
    unsigned int Dialogue::sRecordId = REC_DIAL;

void Dialogue::load(ESMReader &esm)
{
    esm.getSubNameIs("DATA");
    esm.getSubHeader();
    int si = esm.getSubSize();
    if (si == 1)
        esm.getT(mType);
    else if (si == 4)
    {
        // These are just markers, their values are not used.
        int i;
        esm.getT(i);
        esm.getHNT(i, "DELE");
        mType = Deleted;
    }
    else
        esm.fail("Unknown sub record size");
}

void Dialogue::save(ESMWriter &esm) const
{
    if (mType != Deleted)
        esm.writeHNT("DATA", mType);
    else
    {
        esm.writeHNT("DATA", (int)1);
        esm.writeHNT("DELE", (int)1);
    }
}

    void Dialogue::blank()
    {
        mInfo.clear();
    }

}
