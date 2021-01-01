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
