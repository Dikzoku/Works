<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.io.*,java.util.*,java.sql.*"%>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/sql" prefix="sql"%>
<%@ page import="entity.*" %>
<!DOCTYPE html>
<html>
   <head>
      <title>山东大学选课管理系统-教师端</title>
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
 		<li><a href="teacher.jsp">个人信息</a></li>
  		<li><a href="teacher_teach.jsp">授课信息</a></li>
  		<li class="active"><a href="teacher_enter_scores.jsp">成绩录入</a></li>
  		<li><a href="teacher_students.jsp">学生名单</a></li>
  		<li style="float:right"><a href="logout.jsp">退出登录</a></li>
		</ul>
		
	<sql:setDataSource var="snapshot" driver="com.mysql.cj.jdbc.Driver"
     url="jdbc:mysql://localhost:3306/dikzoku?useUnicode=true&serverTimezone=UTC&characterEncoding=utf-8"
     user="root"  password="123456"/>
     

     <%
     	List<SC> sc = new ArrayList<SC>();
		int total = Integer.parseInt(request.getParameter("total"));
     	for(int i=1;i<=total;i++){
     		if(request.getParameter("score"+i)=="") continue;
     		String thesid= request.getParameter("sid"+i);
     		int thescore = Integer.parseInt(request.getParameter("score"+i));
     		SC thesc=new SC(thesid,thescore);
     		sc.add(thesc);
     	}
     	request.setAttribute("sc",sc);
     %>
     	<c:forEach var="row" items="${sc}">
     		<sql:update dataSource="${snapshot}" var="result">
				UPDATE selectcourse
				SET score=?<sql:param value="${row.score}" />
				WHERE sid=?<sql:param value="${row.sid}" /> and cid=?<sql:param value="${param.courseid}" />
			</sql:update>
     	</c:forEach>
     
	<script language='javascript'>
		alert('录入成功！');
		window.location.href="teacher_enter_scores.jsp";
	</script>
   </body>
</html>