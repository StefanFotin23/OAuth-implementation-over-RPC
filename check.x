struct auth_token {
    string token<>;
    string permissions<>;
    int is_signed;
    /* is_signed is a boolean */
};

struct request_access_token_input {
    string client_id<16>;
    struct auth_token auth_token;
};

struct request_access_token_output {
    string access_token<>;
    string generator_token<>;
    int operations_available;
    string request_response<>;
};

struct validate_delegated_action_input {
    string operation<>;
    string resource<>;
    string access_token<>;
};

program CHECKPROG {
    version CHECKVERS {
        struct request_authorization_output request_authorization(string) = 1;
		/* primeste ca parametru: "client_id" */
        struct request_access_token_output request_access_token(struct request_access_token_input) = 2;
        string validate_delegated_action(struct validate_delegated_action_input) = 3;
        struct auth_token approve_request_token(struct auth_token) = 4;
		/* returneaza string: "request_response" */
    } = 1;
} = 0x23072001;