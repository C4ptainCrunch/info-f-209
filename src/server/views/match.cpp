#include "match.h"

using namespace std;

namespace views {

void challenge(JsonValue * message, UserHandler * handler) {
    JsonDict * dictMessage = JDICT(message);

    if (dictMessage == NULL) {
        throw BadRequest("Malformatted request. Need a JSON dict");
    }

    string other_username = getString(dictMessage, "other_username");
    UserHandler * other_handler = handler->findHandler(other_username);
    if(other_handler == NULL){
        return sendFail(handler, 301, "challenge", "User does not exist");
    }

    server_shared_data * server_data = handler->getSharedData();
    Challenge current_challenge = {
        server_data->last_challenge_id++,
        {
            handler->getManager(),
            other_handler->getManager()
        }
    };
    handler->getChalenge_list().push_back(current_challenge);

    JsonDict * payload = new JsonDict();
    payload->add("remote_username", new JsonString(handler->getManager()->getUserName()));
    payload->add("remote_name", new JsonString(handler->getManager()->getName()));
    payload->add("challenge_id", new JsonInt(current_challenge.id));
    other_handler->writeToClient("challenge", payload);
}

} // end namespace
