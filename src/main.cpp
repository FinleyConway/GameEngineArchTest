#include "scene.h"
#include "transform.h"

int main() {
     Scene s(1000);
                                                 //                                        vvv this could be the default parameter 
    s.create_entity().add_component<Trasform>(); // add_component<Transform>(UpdateType::on_event | UpdateType::on_update)

    while (true) {
        s.update();
    }
}