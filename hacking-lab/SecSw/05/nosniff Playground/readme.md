# nosniff Playground
## Lesson learned
If users have the possibility to upload files this could be any MIME type and therefore allowing XSS and compromising.
The risk of such an attack could be reduced by following mitigations.
- Use WAF
- Use a Reverse Proxy
- Allways set the nosniff on the application    
- Check this in the Unit Tests
- Use standard libraries
- Check the file content server-side
