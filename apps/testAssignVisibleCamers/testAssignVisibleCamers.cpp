#include "../../io/BundlerBase.h"
#include "../../io/PlyBase.h"
#include "../../io/PatchBase.h"
#include "../../modules/AssignVisibleCameras/AssignVisibleCameras.h"

int main()
{
    string dir_name = "/home/shujie/WorkSpace/Texture/bin" ;
    Bundler bundler(dir_name);
    PatchReader patchReader(dir_name);

    PlyReader plyReader(dir_name);

    AsgVisCams asgVC = AsgVisCams();
    asgVC.AssignVisCams(patchReader,plyReader);
    asgVC.FindGraphConnections();
    return 0;
}
