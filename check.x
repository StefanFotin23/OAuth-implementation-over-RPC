struct request_access_token_input {
    string client_id<>;
    string auth_token<>;
    int refresh_duration;
};

struct request_access_token_output {
    string resource_access_token<>;
    string refresh_token<>;
    int duration;
    string request_response<>;
};

struct validate_delegated_action_input {
    string client_id<>;
    string operation<>;
    string resource<>;
    string resource_access_token<>;
};

struct validate_delegated_action_output {
    string request_response<>;
    string regenerated_resource_access_token<>;
};

program CHECKPROG {
    version CHECKVERS {
        /* auth_token request_authorization(client_id) */
        string request_authorization(string) = 1;
		
        /* (resource_access_token + refresh_token + duration + request_response) request_access_token(client_id + auth_token) */
        struct request_access_token_output request_access_token(struct request_access_token_input) = 2;
        
        /* struct validate_delegated_action_output (request_response, regenerated_resource_access_token) validate_delegated_action(operation + resource + resource_access_token) */
        struct validate_delegated_action_output validate_delegated_action(struct validate_delegated_action_input) = 3;
        
        /* signed_auth_token approve_request_token(auth_token) */
        string approve_request_token(string) = 4;
    } = 1;
} = 0x23072001;