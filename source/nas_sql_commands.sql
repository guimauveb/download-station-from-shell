/* List */
'SELECT '+selection+' FROM download_queue WHERE '+filter+' '+userClause(options)+' ORDER BY '+options.order+' '+options.direction
/* Clean */
'DELETE FROM download_queue WHERE status = 5 '+userClause(options)
/* Pause */
'UPDATE download_queue SET status = 3 WHERE (status = 1 OR status = 2) '+userClause(options)+" "+idClause(ids)
/* Resume */
'UPDATE download_queue SET status = 1 WHERE (status = 3) '+userClause(options)+" "+idClause(ids)
/* Restart */
'UPDATE download_queue SET status = 1 WHERE (status = 101 OR status = 107) '+userClause(options)+" "+idClause(ids)
/* Remove */
'DELETE FROM download_queue WHERE 1=1 '+userClause(options)+" "+idClause(ids)
/* Add torrent */
/* With given destination */
"INSERT INTO download_queue (username, url, status, filename, pid, created_time, destination) VALUES (%s, %s, 1, %s, -1, %s, %s)"
/* With default destination */
"INSERT INTO download_queue (username, url, status, filename, pid, created_time) VALUES (%s, %s, 1, %s, -1, %s)"
/* Add 
def add(conn, options, urls):
    if options.user == None:
        user = 'admin'
    else:
        user = options.user
    if len(urls) == 0:
        urls = []
        input = '\n'.join(sys.stdin.readlines())
        urls = parseURLs(options.expression, input)
    # earlier versions of DiskStation don't have a target column
    # use only if necessary
    useTarget = options.target != ''
    if useTarget:
        sql = "INSERT INTO download_queue (username, url, status, filename, pid, created_time, destination) VALUES (%s, %s, 1, %s, -1, %s, %s)"
    # TODO - Use a default folder
    else:
        sql = "INSERT INTO download_queue (username, url, status, filename, pid, created_time) VALUES (%s, %s, 1, %s, -1, %s)"
    params = []
    now = int(time.time())
    cursor = conn.cursor()
    ids = []
    for url in urls:
        if useTarget:
            tupel = (user, url, parseFilename(url), now, options.target)
        else:
            tupel = (user, url, parseFilename(url), now)
        params.append(tupel)
        cursor.execute(sql, tupel)
        cursor.execute("SELECT lastval()")
        ids.append(cursor.fetchone()[0])
    // TODO - Return added downloads
    return ids
*/
/* database query helpers **************************************************
def userClause(options):
    if options.user != None:
        return "AND username = '"+options.user+"'"
    return ''

def idClause(ids):
    if ids[0] != 'all':
        return 'AND task_id IN ('+','.join(ids)+')'
    return ''

def createSelection(columns):
    selection = set()
    for col in columns:
        if col in formatters:
            for db_col in formatters[col][0]:
                selection.add(db_col)
        else:
            selection.add(col)
    return ', '.join(selection)
*/

/* Create download_queue table */
CREATE TABLE download_queue(
 task_id integer auto increment,
 username           character varying(128), 
 pid                integer,                
 url                text,                   
 filename           character varying(1024),
 status             integer,                
 created_time       integer,                
 started_time       integer,                
 total_size         bigint,                
 current_size       bigint,                
 current_rate       integer,                
 extra_info         text,                
 total_peers        integer,                
 connected_peers    integer,                
 total_pieces       integer,                
 downloaded_pieces  integer,                
 available_pieces   integer,                
 torrent            bytea,                
 upload_rate        integer,                
 total_upload       bigint,                
 seeding_ratio      integer,                
 seeding_interval   integer,                
 seeding_elapsed    integer,                
 task_flags         integer,                
 seeders            integer,                
 leechers           integer,                
 destination        text,                
 unzip_password     text,                
 unzip_progress     integer,                
 given_filename     text,                
 referer            text,                
 cookie_path        text,                
 thumbnail_status   integer,                
 extra_data         json,                
 completed_time     integer               
);
