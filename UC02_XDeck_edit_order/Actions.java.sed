import lrapi.lr;
import java.sql.*;
import java.util.HashSet;
import java.util.Set;

public class Actions
{
	Set<String> IDset = null;

	public int init(){
		return 0;
	}

	public int action() throws Throwable {
		
		lr.start_transaction("UC02_TR01_Add_task");
		
		String url = "jdbc:oracle:thin:@" + lr.eval_string("{Host}") + ":" 
			+ lr.eval_string("{Port}") + ":" + lr.eval_string("{SID}");
		try (Connection connection = DriverManager.
		    getConnection(url, lr.eval_string("{Login}"), lr.eval_string("{Password}"));
		    Statement statement = connection.createStatement())	{
			
				connection.setAutoCommit(false);
		    	lr.log_message("Connection Success");
		    	IDset = new HashSet<>();
		    	
		    	String sqlRead = "select id from ticket where state_id =  '-1' " +
		    		"and text like 'Ogdanets%'";
		    			    	
		    	try (ResultSet rs = statement.executeQuery(sqlRead)){
		    			while (rs.next()) {
	             		IDset.add(rs.getString("id"));
		    		}
		    		
				} catch (SQLException ex) {
					ex.printStackTrace();
				}
				
		    	try {
		    		
		    		updateIDs(connection, statement);
		    		addTasks(connection, statement);
		    		connection.commit();
		    		
		    	} catch (SQLException ex) {
            		ex.printStackTrace();
                	connection.rollback();
            	}
				
	    }
         catch (SQLException e) {
			e.printStackTrace();
	    	lr.abort();
		}
		
		lr.end_transaction("UC02_TR01_Add_task",lr.PASS);
		return 0;
	}
	
	public void updateIDs(Connection connection, Statement statement) throws Throwable{
		String str = "UPDATE ticket SET state_id = '1'" +
		"WHERE id in (select id from ticket where state_id =  '-1' and text like 'Ogdanets%')";
	    statement.execute(str);
        lr.log_message("Update Success");

	}
	
	public void addTasks(Connection connection, Statement statement) throws Throwable{
		for(String id: IDset) {
			String insert_query = "INSERT INTO task (id, change_id," +
			"ticket_id, guid, header, text, priority_id, state_id," +
	        "client_id, create_date, external_system) select " + id + 
			",'IDC2D620524153zdzPWAoX9OFgW4UB'," + id + ", guid, header, text, '3', '1'," +
			"'106', create_date, 'ASKO' from ticket " +
			"where id = " + id;
	        statement.execute(insert_query);
       	}
		lr.log_message("Insert Success");            
    }
	
	public int end() {
		return 0;
	}
}
