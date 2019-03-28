/**
 * Stage 2
 * 
 * Get data from a connection & parse the data.
 * Using several threads, each gets a connection from the incoming queue,
 * read request from the connection,
 * parse it - determine what page is being requested, check to see if it's alredy cached
 */