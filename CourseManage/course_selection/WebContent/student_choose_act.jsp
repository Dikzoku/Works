<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>

<!DOCTYPE html>
<html>
   <head>
      <title>山东大学选课管理系统-学生端</title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
      <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="https://oss.maxcdn.com/libs/respond.js/1.3.0/respond.min.js"></script>
   </head>
   <body>
   <% request.setCharacterEncoding("UTF-8"); %>
      <script src="https://code.jquery.com/jquery.js"></script>
      <script src="js/bootstrap.min.js"></script>
		
	<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>
     
     <%boolean bl=false;%>
	<c:forEach var="row" items="${paramValues.allcid}">
     <sql:update dataSource="${snapshot}" var="result">
     	insert into selectcourse (sid,cid) 
     	values(?<sql:param value="${user}" />,?<sql:param value="${row}" />);
     </sql:update>
     <%bl=true;%>
	</c:forEach>
	<%if(bl==true){%>
		<script language='javascript'>
			alert('选课成功！');
			window.location.href="student_choose.jsp";
		</script>
	<%}else{%>  
		<script language='javascript'>
			alert('未选择课程，请重新选择！');
			window.location.href="student_choose.jsp";
		</script>
	<%}%>
   </body>
</html>