<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>

<!DOCTYPE html>
<html>
   <head>
      <title>山东大学选课管理系统-管理端</title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
      <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
      <script src="https://oss.maxcdn.com/libs/respond.js/1.3.0/respond.min.js"></script>
   </head>
   <body>
   	<% request.setCharacterEncoding("UTF-8"); %>
      <c:if test="${user==NULL}">
   	  	<script language='javascript'>
			window.location.href="index.jsp";
		</script>
   	  </c:if>
      <script src="https://code.jquery.com/jquery.js"></script>
      <script src="js/bootstrap.min.js"></script>
      
		<ul class="nav nav-tabs">
 		<li><a href="admin.jsp">个人信息</a></li>
  		<li><a href="admin_students.jsp">学生信息</a></li>
  		<li><a href="admin_teachers.jsp">教师信息</a></li>
  		<li class="active"><a href="admin_courses.jsp">课程信息</a></li>
  		<li><a href="admin_departments.jsp">院系信息</a></li>
  		<li style="float:right"><a href="logout.jsp">退出登录</a></li>
		</ul>
		
	<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>
     
     <sql:query dataSource="${snapshot}" var="result">
     	select * from course
     </sql:query>
     
<div class="container">                          
	<table class="table table-hover">
		<thead>
			<h4>课程信息</h4>
			<tr>
   		   		<td><c:out value="课程号"/></td>
   		   		<td><c:out value="课程名"/></td>
   		   		<td><c:out value="先导课程号"/></td>
   		   		<td><c:out value="学分"/></td>
   		   		<td><c:out value="学时"/></td>
   		   		<td><c:out value="所属专业编号"/></td>
		  	</tr>
		</thead>
		<tbody>
		 <c:forEach var="row" items="${result.rows}">
		 	<c:if test="${row.cid==param.thecid}">
		 		<form name="input" action="admin_courses_upd_act.jsp" method="POST">
		 		<input type="hidden" name="cid" value="${row.cid}">
		 		<tr>
		 		<td><c:out value="${row.cid}"/></td>
		 		<td><input type="text" name="cname" placeholder="${row.cname}" value="${row.cname}" style="width:100px"/></td>
		 		<td><input type="text" name="cpreid" placeholder="${row.cpreid}" value="${row.cpreid}" style="width:100px"/></td>
		 		<td><input type="text" name="ccredit" placeholder="${row.ccredit}" value="${row.ccredit}" style="width:100px"/></td>
		 		<td><input type="text" name="ctime" placeholder="${row.ctime}" value="${row.ctime}" style="width:100px"/></td>
		 		<td><input type="text" name="mid" placeholder="${row.mid}" value="${row.mid}" style="width:100px"/></td>
   		    	<td><button type="submit" class="btn btn-default">保存信息</button></td>
   		    	</tr>
   		    	</form>
		 	</c:if>

		 </c:forEach>
		</tbody>
	</table>
</div>
     
   </body>
</html>