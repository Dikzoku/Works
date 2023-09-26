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
  		<li class="active"><a href="admin_teachers.jsp">教师信息</a></li>
  		<li><a href="admin_courses.jsp">课程信息</a></li>
  		<li><a href="admin_departments.jsp">院系信息</a></li>
  		<li style="float:right"><a href="logout.jsp">退出登录</a></li>
		</ul>
		
	<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>
     
    <sql:query dataSource="${snapshot}" var="courses">
     	select * from course where cid=?<sql:param value="${param.cid}"/> 
     </sql:query>
     <sql:query dataSource="${snapshot}" var="hascourses">
     	select * from teachcourse 
     	where cid=?<sql:param value="${param.cid}"/> 
     		and tid=?<sql:param value="${param.tid}"/>
     </sql:query>
     
	<%boolean bl1=false,bl2=false;%>
	
	<c:forEach var="row" items="${hascourses.rows}">
		<%bl1=true;%>
	</c:forEach>
	<%if(bl1==true){%>
		<div class="container">
			<form action="admin_teachers_teach.jsp">
				<h2>已存在该授课信息，请重新输入！</h2>
				<input type="hidden" name="tid" value="${param.tid}"/>
				<input type="hidden" name="tname" value="${param.tname}"/>
				<button type="submit" class="btn btn-default">返回</button>
			</form>
		</div>
	<%}%>
	
	<%if(bl1==false){%>
	
	<c:forEach var="row" items="${courses.rows}">
     <sql:update dataSource="${snapshot}" var="result">
     	insert into teachcourse (cid,tid)
     	value(
     	?<sql:param value="${row.cid}"/> ,
     	?<sql:param value="${param.tid}"/> 
     	)
     </sql:update>
     <%bl2=true;%>
	</c:forEach>
		<%if(bl2==true){%>
			<div class="container">
				<form action="admin_teachers_teach.jsp">
					<h2>添加授课信息成功！</h2>
					<input type="hidden" name="tid" value="${param.tid}"/>
					<input type="hidden" name="tname" value="${param.tname}"/>
					<button type="submit" class="btn btn-default">返回</button>
				</form>
			</div>
		<%}else{%>  
			<div class="container">
				<form action="admin_teachers_teach.jsp">
					<h2>不存在该课程或非本系课程，请重新输入！</h2>
					<input type="hidden" name="tid" value="${param.tid}"/>
					<input type="hidden" name="tname" value="${param.tname}"/>
					<button type="submit" class="btn btn-default">返回</button>
				</form>
			</div>
		<%}%>
	
	
	<%}%>

   </body>
</html>